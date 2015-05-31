#include "worker.h"

#include "options_parser.h"

#include "tinyxml.h"
#include <algorithm>

Worker::Worker(OptionsParser::OperationType type)
{
    switch (type) {
    case OptionsParser::Reverse:
        m_converter = new ReverseConverter;
        break;
    case OptionsParser::Size:
        m_converter = new SizeConverter;
        break;
    default:
        m_converter = 0;
        break;
    }
}

Worker::~Worker()
{
    delete m_converter;
}

bool Worker::process(const OptionsParser &parser)
{
    return this->process(parser.inputFile(), parser.outputFile());
}

bool Worker::process(const std::string &inFile, const std::string &outFile)
{
    if (!m_converter) return false;

    TiXmlDocument doc(inFile);
    if (!doc.LoadFile()) return false;

    this->processElement(doc.FirstChildElement());

    return doc.SaveFile(outFile);
}

//------------------------------------------------------------------------------
void Worker::processElement(TiXmlElement *element)
{
    if (!element) return;

    if ( element->NoChildren() ) {
        this->processAttribute(element->FirstAttribute());
    } else {
        this->processElement(element->FirstChildElement());
    }

    this->processElement(element->NextSiblingElement());
}

void Worker::processAttribute(TiXmlAttribute *attribute)
{
    if (!attribute) return;

    attribute->SetValue( m_converter->convert(attribute->ValueStr()) );

    this->processAttribute(attribute->Next());
}

//CONVERTERS--------------------------------------------------------------------
std::string Worker::ReverseConverter::convert(const std::string &value) const
{
    std::string result(value.substr(3, value.size()-6));

    std::reverse(result.begin(), result.end());

    return result;
}

std::string Worker::SizeConverter::convert(const std::string &value) const
{
    return std::to_string(value.size() - 6);
}
