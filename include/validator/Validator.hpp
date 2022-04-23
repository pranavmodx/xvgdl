#pragma once

#include <iostream>
#include <memory>

#include <xercesc/util/XMLString.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/framework/LocalFileInputSource.hpp>
#include <xercesc/sax/ErrorHandler.hpp>
#include <xercesc/sax/SAXParseException.hpp>
#include <xercesc/validators/common/Grammar.hpp>

XERCES_CPP_NAMESPACE_USE

class WStr
{
private:
    XMLCh*  wStr;

public:
    WStr(const char* str)
    {
        wStr = XMLString::transcode(str);
    }

    ~WStr()
    {
        XMLString::release(&wStr);
    }

    operator const XMLCh*() const
    {
        return wStr;
    }
};

class ParserErrorHandler : public ErrorHandler
{
private:
    void reportParseException(const SAXParseException& ex)
    {
        char* msg = XMLString::transcode(ex.getMessage());
        fprintf(stderr, "at line %llu column %llu, %s\n", 
                ex.getLineNumber(), ex.getColumnNumber(), msg);
        XMLString::release(&msg);
    }

public:
    void warning(const SAXParseException& ex)
    {
        reportParseException(ex);
    }

    void error(const SAXParseException& ex)
    {
        reportParseException(ex);
    }

    void fatalError(const SAXParseException& ex)
    {
        reportParseException(ex);
    }

    void resetErrors()
    {
    }
};

class XVGDLValidator {
    std::unique_ptr<XercesDOMParser> domParser;
    std::unique_ptr<ErrorHandler> parserErrorHandler;

public:
    XVGDLValidator();
    int validateSchema(std::string schemaFilePath, std::string xmlFilePath);
};