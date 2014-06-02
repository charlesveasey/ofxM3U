#include "ofxM3U.h"

#include "Poco/RegularExpression.h"
using Poco::RegularExpression;

void ofxM3U::load(string file){
	isExtended = false;
    ofBuffer buffer = ofBufferFromFile(file);
    string header;
    
    if (buffer.size()) {
        header = buffer.getNextLine();
        if (header == "#EXTM3U"){
            isExtended = true;
            parseExtended(buffer);
        }
        else {
            isExtended = false;
            parseSimple(buffer);
        }
    }
}

void ofxM3U::parseExtended(ofBuffer buffer){
    string header;
    string line;
    string file;
    string title;
    string length;
    
    while(buffer.isLastLine() == false) {
        line = buffer.getNextLine();
        
        if (line.length()) {
            header = line.substr(0, 8);
            header = "#EXTINF:";
            length = (ofSplitString(line, ",")[0]).substr(8);
            title = line.substr(9+length.size());
            title = trimString(title);
            line = buffer.getNextLine();
            file = line;
            createExtendedItem(file, title, ofToInt(length));
        }
    }
}

void ofxM3U::parseSimple(ofBuffer buffer){
    buffer.resetLineReader();
    string line;
    while(buffer.isLastLine() == false) {
        line = buffer.getNextLine();
        if (line.length())
            createSimpleItem(line);
        cout << line << endl;
    }
}

void ofxM3U::createExtendedItem(string file, string title, int length){
    M3UItem item;
    item.file = file;
    item.title = title;
    item.length = length;
    items.push_back(item);
}

void ofxM3U::createSimpleItem(string line){
    M3UItem item;
    item.file = line;
    items.push_back(item);
}

vector<M3UItem> ofxM3U::getItems(){
    return items;
}

void ofxM3U::clear(){
    items.clear();
}

string ofxM3U::trimStringRight(string str) {
    size_t endpos = str.find_last_not_of(" \t\r\n");
    return (string::npos != endpos) ? str.substr( 0, endpos+1) : str;
}

string ofxM3U::trimStringLeft(string str) {
    size_t startpos = str.find_first_not_of(" \t\r\n");
    return (string::npos != startpos) ? str.substr(startpos) : str;
}

string ofxM3U::trimString(string str) {
    return trimStringLeft(trimStringRight(str));
}
