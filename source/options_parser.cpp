#include "options_parser.h"

#include <getopt.h>
#include <sys/stat.h>

OptionsParser::OptionsParser(int argc, char **argv)
{
    struct option options[] =
    {
        {"in", required_argument, 0, 'i'},
        {"out", required_argument, 0, 'o'},
        {"operation", required_argument, 0, 't'},
        {0, 0, 0, 0}
    };

    int c;
    while ( (c = getopt_long (argc, argv, "i:o:t:", options, 0)) != -1 ) {
        switch (c) {
        case 'i':
            m_inputFile = optarg;
            break;

        case 'o':
            m_outputFile = optarg;
            break;

        case 't':
            switch(std::stoi(optarg)) {
            case 1:
                m_operation = Reverse;
                break;
            case 2:
                m_operation = Size;
                break;
            default:
                m_operation = None;
                break;
            }
            break;

            default:
                break;
        }
    }

    struct stat buf;
    if (stat(m_inputFile.c_str(), &buf) == -1) {
        m_error = true;
        m_errorMessage = "Bad input file";
        return;
    }

    if (m_outputFile.empty()) {
        m_error = true;
        m_errorMessage = "Bad output file";
        return;
    }

    if (m_operation == None) {
        m_error = true;
        m_errorMessage = "Bad operation type";
        return;
    }
}

std::string OptionsParser::helpInfo() const
{
    std::string info;

    info += "Usage info:\n\n";
    info += "test-app --in <input path> --out <output path> --operation <operation type (1 or 2)>\n\n";

    return info;
}
