// Author: Jake Rieger
// Created: 8/6/2024.
//

#pragma once

#include "Types.h"

#include <fstream>

namespace IO {
    inline Option<str> Read(const Path& filename) {
        if (!exists(filename) || is_directory(filename)) {
            return kNone;
        }

        std::ifstream file(filename);
        if (!file.is_open()) {
            return kNone;
        }

        str content((std::istreambuf_iterator(file)), std::istreambuf_iterator<char>());
        file.close();

        return content;
    }

    inline Option<Vector<u8>> ReadAllBytes(const Path& filename) {
        if (!exists(filename) || is_directory(filename)) {
            return kNone;
        }

        std::ifstream file(filename, std::ios::binary);
        if (!file.is_open()) {
            return kNone;
        }

        Vector<u8> bytes(std::istreambuf_iterator(file), {});
        file.close();

        return bytes;
    }

    inline Option<Vector<str>> ReadAllLines(const Path& filename) {
        if (!exists(filename) || is_directory(filename)) {
            return kNone;
        }

        std::ifstream file(filename);
        if (!file.is_open()) {
            return kNone;
        }

        Vector<str> lines;
        str line;
        while (std::getline(file, line)) {
            lines.push_back(line);
        }

        file.close();

        return lines;
    }

    inline Option<Vector<u8>>
    ReadBlock(const Path& filename, const u32 blockOffset, const size_t blockSize) {
        if (!exists(filename) || is_directory(filename)) {
            return kNone;
        }

        std::ifstream file(filename, std::ios::binary);
        if (!file.is_open()) {
            return kNone;
        }

        file.seekg(blockOffset, std::ios::beg);
        if (!file.good()) {
            return kNone;
        }

        Vector<u8> buffer(blockSize);
        file.read(RCAST<char*>(buffer.data()), CAST<std::streamsize>(blockSize));

        if (file.gcount() != CAST<std::streamsize>(blockSize)) {
            return kNone;
        }

        return buffer;
    }

    inline bool Write(const Path& filename, const str& content) {
        std::ofstream outfile(filename);
        if (!outfile.is_open()) {
            return false;
        }

        outfile.write(content.c_str(), CAST<std::streamsize>(content.length()));
        outfile.close();

        return true;
    }

    inline bool WriteAllBytes(const Path& filename, const Vector<u8>& bytes) {
        std::ofstream outfile(filename, std::ios::binary);
        if (!outfile.is_open()) {
            return false;
        }

        outfile.write(RCAST<const char*>(bytes.data()), CAST<std::streamsize>(bytes.size()));
        outfile.close();

        return true;
    }

    inline bool WriteAllLines(const Path& filename, const Vector<str>& lines) {
        std::ofstream outfile(filename);
        if (!outfile.is_open()) {
            return false;
        }

        for (const auto& line : lines) {
            outfile << line << std::endl;
        }

        outfile.close();

        return true;
    }
}  // namespace IO