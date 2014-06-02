#pragma once
#include "ofMain.h"
#include "ofMain.h"

class M3UItem {
    
public:
    string file;
    string title;
    int length;
	
};

class ofxM3U {
    
public:
	void load(string file);
    void clear();
    vector<M3UItem> getItems();
    
private:
    vector<M3UItem> items;
    ofBuffer buffer;
    bool isExtended;
    
    void parseExtended(ofBuffer buffer);
    void parseSimple(ofBuffer buffer);

    void createExtendedItem(string file, string title, int length);
    void createSimpleItem(string line);
        
    string trimStringRight(string str);
    string trimStringLeft(string str);
    string trimString(string str);
};

