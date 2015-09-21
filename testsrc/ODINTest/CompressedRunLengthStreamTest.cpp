/******************************************************************************

    ODIN - Open Disk Imager in a Nutshell

    Copyright (C) 2008

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, version 3 of the License.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>

    For more information and the latest version of the source code see
    <http://sourceforge.net/projects/odin-win>

******************************************************************************/
 
#include "stdafx.h"
#include "..\..\src\ODIN\CompressedRunLengthStream.h"
#include "CompressedRunLengthStreamTest.h"
#include <iostream>
using namespace std;

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( CompressedRunLengthStreamTest );


LPCWSTR fileName1 = L"TestRunLength1.dat";
LPCWSTR fileName2 = L"TestRunLength2.dat";
LPCWSTR fileName3 = L"TestRunLength3.dat";
LPCWSTR fileName4 = L"TestRunLength4.dat";

bool CompressedRunLengthStreamTest::sWasDeleted = false;

CompressedRunLengthStreamTest::CompressedRunLengthStreamTest()
{
}

CompressedRunLengthStreamTest::~CompressedRunLengthStreamTest()
{
  if (!sWasDeleted) {
    sWasDeleted = true;
    BOOL ok;
    ok = DeleteFile(fileName1);
    ok = DeleteFile(fileName2);
    ok = DeleteFile(fileName3);
    ok = DeleteFile(fileName4);
  }
}

void 
CompressedRunLengthStreamTest::setUp()
{
}


void 
CompressedRunLengthStreamTest::tearDown()
{
}


void 
CompressedRunLengthStreamTest::simpleTest()
{
    // simple test of base functionality
  BYTE testData[] = {
    0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0x0, 0x0, 0x0, 0x0, 0xF0, 0xFF, 0xFF, 0xFF, 0x0, 0x0, 0x0,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  }; // length: 2688 // run length: 36, 40, 28, 24, 1280, 1280

  HANDLE h = CreateFile(fileName1, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
  CompressedRunLengthStreamWriter writer(h);
  writer.AddBuffer(testData, sizeof(testData)*8);
  writer.Flush();
  unsigned __int64 count0 = writer.Get0Count();
  unsigned __int64 count1 = writer.Get1Count();
  CPPUNIT_ASSERT(count0 == 1344);
  CPPUNIT_ASSERT(count1 == 1344);
  CloseHandle(h);

  DWORD res;
  BYTE expected[] = {/*header*/0, 36, 40, 28, 24, /*header*/05, 00, 05, 00, 05, 00, 00};
  DWORD len = sizeof(expected);
  BYTE *in = new BYTE[len];
  h = CreateFile(fileName1, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
  BOOL ok = ReadFile(h, in, len, &res, NULL);
  CPPUNIT_ASSERT(res == sizeof(expected) && ok);
  for (int i=0; i<sizeof(expected); i++)
    CPPUNIT_ASSERT(in[i] == expected[i]);
  delete [] in;
  CloseHandle(h);
}

void CompressedRunLengthStreamTest::OverflowTest() {
  // test output buffer overflow
  unsigned cBufferSize = 70000;
  BYTE* inputBuffer = new BYTE[cBufferSize];
  unsigned i;
  for (i=0; i<cBufferSize; i++) {
      if (i & 1)
        inputBuffer[i] = 0xFF;
      else
        inputBuffer[i] = 0;
  }
  HANDLE h = CreateFile(fileName2, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
  CompressedRunLengthStreamWriter writer(h);
  writer.AddBuffer(inputBuffer, cBufferSize*8);
  writer.Flush();
  CloseHandle(h);
  unsigned __int64 count0 = writer.Get0Count();
  unsigned __int64 count1 = writer.Get1Count();
  CPPUNIT_ASSERT(count0 == 280000);
  CPPUNIT_ASSERT(count1 == 280000);
  
  // check ouput
  DWORD lenExpected = 87505;
  DWORD lenToRead = 100000;
  DWORD res;
  BYTE* in = new BYTE[lenToRead];
  h = CreateFile(fileName2, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
  BOOL ok = ReadFile(h, in, lenToRead, &res, NULL);
  CPPUNIT_ASSERT(res == lenExpected && ok);
  CPPUNIT_ASSERT(in[0] == 0);
  CPPUNIT_ASSERT(in[1] == 0);
  CPPUNIT_ASSERT(in[2] == 8);
  CPPUNIT_ASSERT(in[3] == 8);
  CPPUNIT_ASSERT(in[4] == 8);
  CPPUNIT_ASSERT(in[5] == 0);
  CPPUNIT_ASSERT(in[6] == 8);
  CPPUNIT_ASSERT(in[7] == 8);
  CPPUNIT_ASSERT(in[9] == 8);
  CPPUNIT_ASSERT(in[10] == 0);
  CPPUNIT_ASSERT(in[11] == 8);
  CPPUNIT_ASSERT(in[87499] == 8);
  CPPUNIT_ASSERT(in[87500] == 0);
  CPPUNIT_ASSERT(in[87501] == 8);
  CPPUNIT_ASSERT(in[87502] == 0);
  CPPUNIT_ASSERT(in[87503] == 0);
  CPPUNIT_ASSERT(in[87504] == 0);
  delete [] in;
  CloseHandle(h);

  // repeat test but without padding at the end so that no 0 run length are added
 for (i=0; i<cBufferSize; i++) {
      if (i & 1)
        inputBuffer[i] = 0x0;
      else
        inputBuffer[i] = 0xFF;
  }
  h = CreateFile(fileName3, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
  CompressedRunLengthStreamWriter writer2(h);
  writer2.AddBuffer(inputBuffer, cBufferSize*8);
  writer2.Flush();
  CloseHandle(h);
  delete [] inputBuffer;

  // check ouput
  lenExpected = 87500;
  lenToRead = 100000;  
  in = new BYTE[lenToRead];
  h = CreateFile(fileName3, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
  ok = ReadFile(h, in, lenToRead, &res, NULL);
  CPPUNIT_ASSERT(res == lenExpected && ok);
  CPPUNIT_ASSERT(in[0] == 0);
  CPPUNIT_ASSERT(in[1] == 8);
  CPPUNIT_ASSERT(in[2] == 8);
  CPPUNIT_ASSERT(in[3] == 8);
  CPPUNIT_ASSERT(in[4] == 8);
  CPPUNIT_ASSERT(in[5] == 0);
  CPPUNIT_ASSERT(in[6] == 8);
  CPPUNIT_ASSERT(in[7] == 8);
  CPPUNIT_ASSERT(in[8] == 8);
  CPPUNIT_ASSERT(in[9] == 8);
  CPPUNIT_ASSERT(in[10] == 0);
  CPPUNIT_ASSERT(in[11] == 8);
  CPPUNIT_ASSERT(in[87494] == 8);
  CPPUNIT_ASSERT(in[87495] == 0);
  CPPUNIT_ASSERT(in[87496] == 8);
  CPPUNIT_ASSERT(in[87497] == 8);
  CPPUNIT_ASSERT(in[87498] == 8);
  CPPUNIT_ASSERT(in[87499] == 8);
  delete [] in;
  CloseHandle(h);
}

void CompressedRunLengthStreamTest::ContinueSequenceTest()
{
 // test continueing last token after loading a second buffer
 unsigned cBufferSize = 100;
 BYTE* inputBuffer0 = new BYTE[cBufferSize];
 BYTE* inputBuffer1 = new BYTE[cBufferSize];
 for (unsigned i=0; i<cBufferSize; i++) {
        inputBuffer0[i] = 0xFF;
        inputBuffer1[i] = 0;
  }
  HANDLE h = CreateFile(fileName4, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
  CompressedRunLengthStreamWriter writer3(h);
  writer3.AddBuffer(inputBuffer0, cBufferSize*8);
  writer3.AddBuffer(inputBuffer1, cBufferSize*8);
  writer3.AddBuffer(inputBuffer1, cBufferSize*8);
  writer3.AddBuffer(inputBuffer0, cBufferSize*2);
  writer3.Flush();
  CloseHandle(h);
  delete [] inputBuffer0;
  delete [] inputBuffer1;
  CPPUNIT_ASSERT(writer3.Get0Count() == 1600);
  CPPUNIT_ASSERT(writer3.Get1Count() == 1000);
  
  // check ouput
  unsigned lenToRead = 100;
  DWORD res;
  BYTE expected2[] = {/*header*/0x05, 0x20, 0x03, 0x40, 0x06, 0xC8, 0x00};
  BYTE* in = new BYTE[lenToRead];
  h = CreateFile(fileName4, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
  BOOL ok = ReadFile(h, in, lenToRead, &res, NULL);
  CPPUNIT_ASSERT(res == sizeof(expected2) && ok);
  for (int i=0; i<sizeof(expected2); i++)
    CPPUNIT_ASSERT(in[i] == expected2[i]);
  delete[] in;
  CloseHandle(h);
}

void CompressedRunLengthStreamTest::ReaderTest1() {
  unsigned bufferSize = 100000;
  BYTE *buffer = new BYTE[bufferSize];
  DWORD len;

  HANDLE h = CreateFile(fileName1, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
  // BOOL ok = ReadFile(h, buffer, bufferSize, &len, NULL);
  LARGE_INTEGER li;
  ::GetFileSizeEx(h, &li);
  len = li.LowPart;
  CompressedRunLengthStreamReader reader(h, 0, len);
  unsigned __int64 token;
  unsigned expected[] = { 36, 40, 28, 24, 1280, 1280};
  unsigned i = 0;

  while (!reader.LastValueRead()) {
    token = reader.GetNextRunLength();
    CPPUNIT_ASSERT(expected[i++] == token);
  }
  CPPUNIT_ASSERT(i == sizeof(expected)/sizeof(expected[0]));
  CloseHandle(h);
}

void CompressedRunLengthStreamTest::ReaderTest2() {
  unsigned bufferSize = 100000;
  BYTE *buffer = new BYTE[bufferSize];
  DWORD len;

  HANDLE h = CreateFile(fileName2, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
  // BOOL ok = ReadFile(h, buffer, bufferSize, &len, NULL);
  LARGE_INTEGER li;
  ::GetFileSizeEx(h, &li);
  len = li.LowPart;
  CompressedRunLengthStreamReader reader(h, 0, len);
  unsigned __int64 token;
  unsigned i = 0;

  // first run length must be 0
  token = reader.GetNextRunLength();
  ++i;
  CPPUNIT_ASSERT(0 == token);
    
  while (!reader.LastValueRead()) {
    token = reader.GetNextRunLength();
    ++i;
    CPPUNIT_ASSERT(8 == token);
  }
  CPPUNIT_ASSERT(i == 70001);
  CloseHandle(h);
}

void CompressedRunLengthStreamTest::ReaderTest3() {
  unsigned bufferSize = 100000;
  BYTE *buffer = new BYTE[bufferSize];
  DWORD len;

  HANDLE h = CreateFile(fileName3, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
  
  LARGE_INTEGER li;
  ::GetFileSizeEx(h, &li);
  len = li.LowPart;
  CompressedRunLengthStreamReader reader(h, 0, len);
  unsigned __int64 token;
  unsigned i = 0;
  while (!reader.LastValueRead()) {
    token = reader.GetNextRunLength();
    ++i;
    CPPUNIT_ASSERT(8 == token);
  }
  CPPUNIT_ASSERT(i == 70000);  
  CloseHandle(h);
}

void CompressedRunLengthStreamTest::ReaderTest4() {
  unsigned bufferSize = 100000;
  BYTE *buffer = new BYTE[bufferSize];
  DWORD len;

  HANDLE h = CreateFile(fileName4, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
  
  LARGE_INTEGER li;
  ::GetFileSizeEx(h, &li);
  len = li.LowPart;
  CompressedRunLengthStreamReader reader(h, 0, len);
  unsigned __int64 token;
  unsigned expected[] = {800, 1600, 200};

  unsigned i = 0;
  while (!reader.LastValueRead()) {
    token = reader.GetNextRunLength();
    CPPUNIT_ASSERT(expected[i++] == token);
  }
  CPPUNIT_ASSERT(i == sizeof(expected)/sizeof(expected[0]));
  CloseHandle(h);
}

void 
CompressedRunLengthStreamTest::extraLenTest()
{
    // simple test of base functionality
  BYTE testData[] = {
    0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0x0, 0x0, 0x0, 0x0, 0xF0, 0xFF, 0xFF, 0xFF, 0x0, 0x0, 0x0,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  }; // length: 2688 // run length: 36, 40, 28, 24, 1280, 1280

  const unsigned extraLen = 100;
  HANDLE h = CreateFile(fileName1, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
  CompressedRunLengthStreamWriter writer(h, extraLen);
  writer.AddBuffer(testData, sizeof(testData)*8);
  writer.Flush();
  unsigned __int64 count0 = writer.Get0Count();
  unsigned __int64 count1 = writer.Get1Count();
  CPPUNIT_ASSERT(count1 == 1444);
  CPPUNIT_ASSERT(count0 == 1344);
  CloseHandle(h);

  DWORD res;
  BYTE expected[] = {/*header*/0, 136, 40, 28, 24, /*header*/05, 00, 05, 00, 05, 00, 00};
  DWORD len = sizeof(expected);
  BYTE *in = new BYTE[len];
  h = CreateFile(fileName1, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
  BOOL ok = ReadFile(h, in, len, &res, NULL);
  CPPUNIT_ASSERT(res == sizeof(expected) && ok);
  for (int i=0; i<sizeof(expected); i++)
    CPPUNIT_ASSERT(in[i] == expected[i]);
  delete [] in;
  CloseHandle(h);
}

void 
CompressedRunLengthStreamTest::extraLenTest2()
{
    // simple test of base functionality
  BYTE testData[] = {
    /*0xFF, 0xFF, 0xFF, 0xFF, 0x0F, */0x0, 0x0, 0x0, 0x0, 0xF0, 0xFF, 0xFF, 0xFF, 0x0, 0x0, 0x0,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  }; // length: 2688 // run length: 36, 40, 28, 24, 1280, 1280

  const unsigned extraLen = 100;
  HANDLE h = CreateFile(fileName1, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
  CompressedRunLengthStreamWriter writer(h, extraLen);
  writer.AddBuffer(testData, sizeof(testData)*8);
  writer.Flush();
  unsigned __int64 count0 = writer.Get0Count();
  unsigned __int64 count1 = writer.Get1Count();
  CPPUNIT_ASSERT(count1 == 1408);
  CPPUNIT_ASSERT(count0 == 1340);
  CloseHandle(h);

  DWORD res;
  BYTE expected[] = {/*header*/0, 100, 36, 28, 24, /*header*/05, 00, 05, 00, 05, 00, 00};
  DWORD len = sizeof(expected);
  BYTE *in = new BYTE[len];
  h = CreateFile(fileName1, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
  BOOL ok = ReadFile(h, in, len, &res, NULL);
  CPPUNIT_ASSERT(res == sizeof(expected) && ok);
  for (int i=0; i<sizeof(expected); i++)
    CPPUNIT_ASSERT(in[i] == expected[i]);
  delete [] in;
  CloseHandle(h);
} 