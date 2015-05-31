#ifndef WORKER_H
#define WORKER_H

#include <string>
#include "options_parser.h"

class TiXmlElement;
class TiXmlAttribute;

class Worker {

    class AbstractConverter {
    public:
        virtual std::string convert(const std::string &value) const = 0;
    };

    class ReverseConverter : public AbstractConverter {
    public:
        std::string convert(const std::string &value) const;
    };

    class SizeConverter : public AbstractConverter {
    public:
        std::string convert(const std::string &value) const;
    };

public:
    Worker(OptionsParser::OperationType type);
    ~Worker();

    bool process(const OptionsParser &parser);
    bool process(const std::string &inFIle, const std::string &outFIle);

private:
    void processElement(TiXmlElement *element);
    void processAttribute(TiXmlAttribute *attribute);

private:
    AbstractConverter *m_converter = 0;
};

#endif
