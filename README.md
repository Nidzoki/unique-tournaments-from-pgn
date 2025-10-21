# 🎯 TournamentExtractor — PGN Tournament Name Extractor

## 📘 Overview
`TournamentExtractor` is a C++ utility designed to efficiently extract unique tournament names from large PGN (Portable Game Notation) files containing chess games. It is optimized for performance and scalability, capable of processing millions of games with real-time progress reporting and clean output.

---

## ⚙️ Features
- Parses PGN files line by line, searching for `[Event "Tournament Name"]` headers.
- Deduplicates tournament names using `std::unordered_set`.
- Displays progress every 50,000 games processed.
- Writes results to a `.txt` file.
- Measures and reports total processing time.

---

## 🚀 Usage

### 🔧 Compilation
```bash
g++ -std=c++17 -O2 tournament_extractor.cpp -o tournament_extractor
```

### ▶️ Execution
```bash
./tournament_extractor <input.pgn>
```

### 📌 Example
```bash
./tournament_extractor huge_4m_games.pgn
```

This will create a file named `tournament_names.txt` containing all unique tournament names.

---

## 🧩 Code Structure

### Class: `TournamentExtractor`

#### 🔹 Constructor
```cpp
TournamentExtractor(const std::string& input_file, const std::string& output_file_name);
```
- Opens the input PGN file and prepares the output file.
- Throws `std::runtime_error` if either file cannot be opened.

#### 🔹 Destructor
```cpp
~TournamentExtractor();
```
- Closes open file streams.

#### 🔹 Method: `extractTournamentNames()`
```cpp
void extractTournamentNames();
```
- Reads the PGN file line by line.
- Extracts tournament names from `[Event "..."]` headers.
- Tracks the number of games processed.
- Reports progress every 50,000 games.
- Writes all unique tournament names to the output file.
- Displays summary statistics and total time taken.

---

## 📄 Output

- **File**: `tournament_names.txt`
- **Content**: One tournament name per line, deduplicated.

---

## 📚 Dependencies
- Standard C++17 libraries:
  - `<iostream>`
  - `<fstream>`
  - `<string>`
  - `<unordered_set>`
  - `<chrono>`

---

## 🧠 Performance Notes
- Designed to handle PGN files with millions of games.
- Uses `std::unordered_set` for fast deduplication.
- Minimal memory footprint per game.
- Real-time progress feedback for long-running tasks.

---

## 🛠 Potential Extensions
- Extract additional headers: `[Site]`, `[Date]`, `[Round]`.
- Allow custom output file name via command-line argument.
- Sort tournament names alphabetically before writing.
- Export to CSV or JSON for downstream analytics.

---
## 📂 PGN Dataset Source

This project was tested using a large PGN file from the AjedrezData over-the-board database:

👉 [Over-the-Board Database — AJ-OTB-000](https://ajedrezdata.com/databases/otb/over-the-board-database-aj-otb-000/)

Due to file size, the PGN file is not included in this repository. You can download it manually from the link above by clicking on AJ-OTB-PGN-000 download button.

---
## 📄 License
This project is licensed under the [MIT License](LICENSE).
