#include "stdafx.h"
#include "Helper_functions.h"
#include <sapi.h>			//Microsoft speech api
//#include <sphelper.h>		//for SpFindBestToken
//helper functions

bool isvovel(const char & character){
	const char vovels[]{ 'a', 'e', 'i', 'o', 'u' };
	for (int i = 0; i < (sizeof(vovels) / sizeof(*vovels)); i++) {
		if (character == vovels[i]) return true;
	};
	return false;
	//date of creation: 06.09.2017
};

int speak(const std::wstring & text){
	ISpVoice * pVoice = NULL;	//not mandatory - just initializing 

	if (FAILED(::CoInitialize(NULL)))
		return FALSE;

	//setup
	HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void **)&pVoice);

	//attempt to change default voice parameters programatically
	//ISpObjectToken* cpToken(NULL);								//voice token creation
	//SpFindBestToken(SPCAT_VOICES, L"language=english", L"", &cpToken);	//finding best suiting voice to parameters
	//pVoice->SetVoice(cpToken);									//setting initialized voice to token
	//cpToken->Release();											//releasing token

	if (SUCCEEDED(hr))	{
		//hr = pVoice->Speak(text.c_str(), 0, NULL);		//need to figure out a way to convert std::string to wchar_t(LPCWSTR)
		//std::wcout << "Atempting to speak: " << text.c_str() << ".\n";
		hr = pVoice->Speak(text.c_str(), 0, NULL);
		//hr = pVoice->Speak(L"Test, test, test.", 0, NULL);		//actual speech - needs text in wchar_t in order to work

		pVoice->Release();
		pVoice = NULL;
	}
	::CoUninitialize();
	return TRUE;
}

std::vector<std::string> Tokenize(const std::string &String, const char delimiter) {
	size_t position = 0;
	std::vector<std::string> Tokenized = {};

	while (position < String.length()) {
		Tokenized.push_back(String.substr(position, String.find(delimiter, position) - position));
		if (position != String.length()) position = String.find_first_not_of(delimiter, String.find(delimiter, position));
	};
	return Tokenized;
};

std::string Get_unique_characters(const std::string & input, const std::string & ignore) {
	std::string found_characters{};
	for (int i = 0; i < input.length(); i++) {
		const char & character = input.at(i);
		bool unique = true;
		for each (auto found in found_characters) {
			if (character == found) { unique = false; break; }
		};
		for each (auto found in ignore) {
			if (character == found) { unique = false; break; }
		};

		if (unique) { found_characters += character; };
	};
	return found_characters;
};