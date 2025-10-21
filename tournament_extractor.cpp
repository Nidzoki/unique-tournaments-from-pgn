#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <chrono>

class TournamentExtractor {
private:
    std::ifstream pgn_file;
    std::ofstream output_file;
    std::unordered_set<std::string> tournament_names;
    int games_processed;

public:
    TournamentExtractor(const std::string& input_file, const std::string& output_file_name) 
        : games_processed(0) {
        pgn_file.open(input_file);
        if (!pgn_file.is_open()) {
            throw std::runtime_error("Cannot open PGN file: " + input_file);
        }
        
        output_file.open(output_file_name);
        if (!output_file.is_open()) {
            throw std::runtime_error("Cannot create output file: " + output_file_name);
        }
    }
    
    ~TournamentExtractor() {
        if (pgn_file.is_open()) pgn_file.close();
        if (output_file.is_open()) output_file.close();
    }
    
    void extractTournamentNames() {
        std::string line;
        std::string current_tournament;
        
        auto start_time = std::chrono::high_resolution_clock::now();
        auto last_report = start_time;
        
        std::cout << "Extracting tournament names from 4.4M games...\n";
        
        while (std::getline(pgn_file, line)) {
            // Look for Event headers
            if (line.find("[Event \"") == 0) {
                size_t start = 8; // Skip "[Event "
                size_t end = line.find_last_of('"');
                if (end != std::string::npos && end > start) {
                    current_tournament = line.substr(start, end - start);
                    
                    // Add to set (automatically handles duplicates)
                    if (tournament_names.find(current_tournament) == tournament_names.end()) {
                        tournament_names.insert(current_tournament);
                    }
                }
            }
            
            // Count games and report progress
            if (line.empty()) {
                games_processed++;
                
                if (games_processed % 50000 == 0) {
                    auto now = std::chrono::high_resolution_clock::now();
                    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - last_report).count();
                    
                    std::cout << "Processed " << games_processed << " games (" 
                              << tournament_names.size() << " unique tournaments so far)... "
                              << elapsed << "s since last report\n";
                    
                    last_report = now;
                }
            }
        }
        
        // Write all unique tournament names to file
        std::cout << "Writing " << tournament_names.size() << " unique tournaments to file...\n";
        
        for (const auto& name : tournament_names) {
            output_file << name << "\n";
        }
        
        auto end_time = std::chrono::high_resolution_clock::now();
        auto total_duration = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);
        
        std::cout << "SUCCESS!\n";
        std::cout << "Total games processed: " << games_processed << "\n";
        std::cout << "Unique tournaments found: " << tournament_names.size() << "\n";
        std::cout << "Time taken: " << total_duration.count() << " seconds\n";
        std::cout << "Output: tournament_names.txt\n";
    }
};

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <input.pgn>\n";
        std::cout << "Example: " << argv[0] << " huge_4m_games.pgn\n";
        return 1;
    }
    
    std::string input_file = argv[1];
    std::string output_file = "tournament_names.txt";
    
    try {
        TournamentExtractor extractor(input_file, output_file);
        extractor.extractTournamentNames();
        
    } catch (const std::exception& e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}