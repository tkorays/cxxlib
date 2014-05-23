#ifndef _TK_FACESTORAGE_IMPL_H_
#define _TK_FACESTORAGE_IMPL_H_
#pragma once

#include "../ext/tinyxml/tinyxml.h"

// Impliment for class Face
Face::Face(){
}
int Face::getId(){
	return id;
}
void Face::setId(int id_){
	id = id_;
}
string Face::getName(){
	return name;
}
void Face::setName(string name_){
	name = name_;
}
void Face::clearImages(){
	images.clear();
}
void Face::addImage(string img){
	bool contains = false;
	vector<string>::iterator img_it = images.begin();
	while(img_it != images.end() && !contains){
		contains = (*img_it)==img ? true : false;
		img_it++;
	}
	if(!contains){
		images.push_back(img);
	}
}
void Face::updata(int id_,string name_){
	setId(id_);
	setName(name_);
}


// Impliment for class FaceStorage
size_t FaceStorage::size() {
	return faces.size();
}
bool FaceStorage::load(const string filename){
	file = filename;

	TiXmlDocument* doc = new TiXmlDocument(file.c_str());
	doc->LoadFile();
	TiXmlElement* root = doc->RootElement();

	TiXmlElement* face = root->FirstChildElement();
	while (face) {
		int id;
		string name;
		face->Attribute("id", &id);
		name = face->Attribute("name");

		Face fc;
		fc.updata(id, name);
		TiXmlElement* img = face->FirstChildElement();
		while (img) {
			TiXmlText* img_str = (TiXmlText*)img->FirstChild();
			fc.addImage(img_str->Value());
			img = img->NextSiblingElement();
		}
		faces.push_back(fc);
		face = face->NextSiblingElement();
	}

	return true;

}
bool FaceStorage::save(const string filename) {
	
	TiXmlDocument* doc = new TiXmlDocument();
	TiXmlDeclaration* declare = new TiXmlDeclaration("1.0", "UTF-8", "no");
	doc->LinkEndChild(declare);

	TiXmlElement* root = new TiXmlElement("faces");
	doc->LinkEndChild(root);

	
	for (size_t i = 0; i < faces.size(); i++) {
		TiXmlElement* face = new TiXmlElement("face");
		face->SetAttribute("id", faces[i].getId());
		face->SetAttribute("name", (faces[i].getName()).c_str());
		

		for (size_t j = 0; j < faces[i].images.size(); j++) {
			TiXmlText* img_str = new TiXmlText("img");
			
			TiXmlElement* img = new TiXmlElement("img");
			img_str->SetValue(faces[i].images[j].c_str());
			
			img->LinkEndChild(img_str);

			face->LinkEndChild(img);
		}
		root->LinkEndChild(face);
	}
	bool status = doc->SaveFile(filename.c_str());
	doc->Clear(); // free memory 
	return status;
}
// TODO: do not know it's necessery
Face FaceStorage::getFaceById(int id){
	return Face();
}
// TODO: do not know it's necessery
Face FaceStorage::getFaceByName(string name){
	return Face();
}
vector<Face> FaceStorage::getAllFaces(){
	return faces; 
}
bool FaceStorage::operator<<(Face face){
	faces.push_back(face);
	return true;
}
bool FaceStorage::operator>>(vector<Face>& faces_) {
	faces_ = faces;
	return true;
}
string FaceStorage::getNameById(int id) {
	vector<Face>::iterator face_it = faces.begin();
	while (face_it!=faces.end()) {
		if ((*face_it).getId()==id) {
			return (*face_it).getName();
		}
		face_it++;
	}
	return "";
}



#endif //  _TK_FACESTORAGE_IMPL_H_
