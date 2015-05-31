#ifndef OPTIONS_PARSER_H
#define OPTIONS_PARSER_H

#include <string>

class OptionsParser {

public:
    enum OperationType {
        Reverse,
        Size,
        None
    };

    OptionsParser(int argc, char **argv);

    std::string inputFile() const { return m_inputFile; }
    std::string outputFile() const { return m_outputFile; }
    OperationType operationType() const { return m_operation; }

    bool hasError() const { return m_error; }
    std::string errorMessage() const { return m_errorMessage; }

    std::string helpInfo() const;

private:
    std::string m_inputFile, m_outputFile;
    std::string m_errorMessage;
    OperationType m_operation = None;
    bool m_error = false;
};

#endif
