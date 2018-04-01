#include "ofxM3U.h"

#include "Poco/RegularExpression.h"
using Poco::RegularExpression;

void ofxM3U::load(string file){
	isExtended = false;
    ofBuffer buffer = ofBufferFromFile(file);
    string header;

    ofBuffer::Lines lines = buffer.getLines();

    if (buffer.size()) {
        header = trimString(*lines.begin());
        if (header == "#EXTM3U"){
            isExtended = true;
            parseExtended(lines);
        }
        else {
            isExtended = false;
            parseSimple(lines);
        }
    }
}

void ofxM3U::parseExtended(ofBuffer::Lines lines){
    string header;
    string line;
    string file;
    string title;
    string length;

    ofBuffer::Line iter = lines.begin();
    // Skip first line
    iter++;

    while (iter != lines.end()) {
        line = trimString(*iter++);
        
        if (line.length() > 0) {
            header = line.substr(0, 8);
            header = "#EXTINF:";
            length = (ofSplitString(line, ",")[0]).substr(8);
            title = line.substr(9+length.size());
            title = trimString(title);
            file = *iter++;
            createExtendedItem(file, title, ofToInt(length));
        }
    }
}

void ofxM3U::parseSimple(ofBuffer::Lines lines) {
    ofBuffer::Line iter = lines.begin();
    string line;
    while (iter != lines.end()) {
        line = trimString(*iter++);
        if (line.length() > 0)
            createSimpleItem(line);
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
    size_t endpos = str.find_last_not_of(" ");
    cout << str << " " << endpos << endl;
    return (string::npos != endpos) ? str.substr(0, endpos+1) : str;
}

string ofxM3U::trimStringLeft(string str) {
    size_t startpos = str.find_first_not_of(" ");
    return (string::npos != startpos) ? str.substr(startpos) : str;
}

string ofxM3U::trimString(string str) {
    string::size_type pos = str.find_last_not_of(' ');
    if(pos != string::npos) {
        str.erase(pos + 1);
        pos = str.find_first_not_of(' ');
        if(pos != string::npos) str.erase(0, pos);
    }
    else str.erase(str.begin(), str.end());
    return str;
}
