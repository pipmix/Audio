#include "stdafx.h"
#include "WaveFile.h"

WaveFile::WaveFile(){
	m_waveFormat = { 0 };
	m_buffer = { 0 };
	m_data = nullptr;
}

WaveFile::~WaveFile() {
	delete[] m_data;
	m_data = nullptr;

}

void WaveFile::Create()
{







}
void WaveFile::Load(char* fileName) {


}