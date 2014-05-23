#ifndef _TK_FACESTORAGE_H_
#define _TK_FACESTORAGE_H_
#pragma once

#include <string>
#include <vector>
using namespace std;

// face 
class Face{
private:
	int id;
	string name;
public:
	vector<string> images;
	Face();
	int getId();
	void setId(int id_);
	string getName();
	void setName(string name_);
	void clearImages();
	void addImage(string img);
	void updata(int id_, string name_);
};

// facestorage
class FaceStorage{
private:
	string file;
public:
	vector<Face> faces;
	size_t size();
	bool load(const string filename);
	bool save(const string filename);
	Face getFaceById(int id);
	Face getFaceByName(string name);
	vector<Face> getAllFaces();
	string getNameById(int id);
	bool operator<<(Face face);
	bool operator>>(vector<Face>& faces_);
};

#include "FaceStorage_impl.h"

#endif // _TK_FACESTORAGE_H_
