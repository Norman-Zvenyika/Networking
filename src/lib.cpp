//cite homwork 8
#include <vector>
#include <stdio.h>
#include <ostream>
#include <iostream>
#include <sstream>
#include "pack109.hpp"
using namespace std;

//bool serialization
vec pack109::serialize(bool item)
{
  vec bytes;
  if (item == true){
    bytes.push_back(PACK109_TRUE);
  }
  else{
    bytes.push_back(PACK109_FALSE);
  }
  return bytes;
}

//bool deserialization
bool pack109::deserialize_bool(vec bytes){
  if (bytes.size() < 1){
    throw;
  }
  if (bytes[0] == PACK109_TRUE){
    return true;
  }
  else if (bytes[0] == PACK109_FALSE){
    return false;
  }
  else{
    throw;
  }
}

//u8 serialization
vec pack109::serialize(u8 item){
  vec bytes;
  bytes.push_back(PACK109_U8);
  bytes.push_back(item);
  return bytes;
}

//u8 deserialization
u8 pack109::deserialize_u8(vec bytes){
  if (bytes.size() < 2){
    throw;
  }
  if (bytes[0] == PACK109_U8){
    return bytes[1];
  }
  else{
    throw;
  }
}

// u32 serialization
vec pack109::serialize(u32 item){
  vec bytes; // 1 tag byte + 4 int byes
  bytes.push_back(PACK109_U32);
  int i = (sizeof(u32) * 2) - 2;
  for (i; i >= 0; i -= 2){
    int shift = (item >> i * 4);
    u8 byte = shift & 0x000000FF;
    bytes.push_back((u8)byte);
  }
  return bytes;
}

//u32 deserialization
u32 pack109::deserialize_u32(vec bytes) {
  u32 result = 0;
  if (bytes[0] == PACK109_U32){
    int j = (sizeof(u32) * 2) - 2;
    for (int i = 1; i <= sizeof(u32); i++){
      u32 shifted = (u32)bytes[i] << j * 4;
      result = result | shifted;
      j -= 2;
    }
    return result;
  }
  else{
    throw;
  }
}

//u64 serialization
vec pack109::serialize(u64 item) {
  vec bytes;
  bytes.push_back(PACK109_U64);
  for(int i= 7; i>=0;i--) {
    u64 shifted = item >> (8 * i);
    bytes.push_back((u8) shifted & 0x00000000000000FF);
  }
  return bytes;
}

//u64 deserialize
u64 pack109::deserialize_u64(vec bytes) {
  u64 result = 0;
  if(bytes[0] == PACK109_U64) {
    int posOfByte = 1;
    for(int i=7; i>=0; i--) {
      u64 shifted = (u64)(bytes[posOfByte]) << (8*i);
      result = result | shifted;
      posOfByte++;
    }
    return result;
  }
  else {
    throw;
  }
}

//i8 serialize
vec pack109::serialize(i8 item) {
  vec bytes;
  bytes.push_back(PACK109_I8);
  bytes.push_back((u8)item);   //size of i8 is 1 byte, which is equivalent to u8
  return bytes;
}

//i8 deserialize
i8 pack109::deserialize_i8(vec bytes) {
  if (bytes[0] == PACK109_I8) {
    return (i8)bytes[1];
  } 
  else {
    throw;
  }
}

//i32 serialize
vec pack109::serialize(i32 item) {
  vec bytes;
  bytes.push_back(PACK109_I32);
  for(int i= 3; i>=0;i--) {
    i32 shifted = item >> (8 * i);
    bytes.push_back((u8) shifted & 0x000000FF);
  }
  return bytes;
}

//i32 deserialize
i32 pack109::deserialize_i32(vec bytes) {
  i32 result = 0;
  if(bytes[0] == PACK109_I32) {
    int posOfByte = 1;
    for(int i=3; i>=0; i--) {
      i32 shifted = (u64)(bytes[posOfByte]) << (8*i);
      result = result | shifted;
      posOfByte++;
    }
    return result;
  }
  else {
    throw;
  }
}

//i64 serialize
vec pack109::serialize(i64 item) {
  vec bytes;
  bytes.push_back(PACK109_I64);
  for(int i= 7; i>=0;i--) {
    i64 shifted = item >> (8 * i);
    bytes.push_back((u8) shifted & 0x00000000000000FF);
  }
  return bytes;
}

//i64 deserialize
i64 pack109::deserialize_i64(vec bytes) {
  i64 result = 0;
  if(bytes[0] == PACK109_I64) {
    int posOfByte = 1;
    for(int i=7; i>=0; i--) {
      i64 shifted = (i64)(bytes[posOfByte]) << (8*i);
      result = result | shifted;
      posOfByte++;
    }
    return result;
  }
  else {
    throw;
  }
}

//f32 serialize
vec pack109::serialize(f32 item) {
  vec bytes;
  u32* f32Item = (u32*) (&item);
  bytes.push_back(PACK109_F32);
  for(int i= 3; i>=0;i--) {
    u32 shifted = *f32Item >> (8 * i);
    bytes.push_back((u8) shifted & 0x000000FF);
  }
  return bytes;
}

//f32 deserialize
f32 pack109::deserialize_f32(vec bytes){
  u32 result = 0;
  if (bytes[0] == PACK109_F32) {
    int j = (sizeof(u32) * 2) - 2;
    for(int i=1; i <= sizeof(u32); i++) {
      u32 shifted = (u32) bytes[i] << j * 4;
      result = result | shifted;
      j-=2;
    }
    f32 *f32Pointer = (f32*) (&result);  //change the u32 to f32
    return *f32Pointer;
  } 
  else {
    throw;
  }
}

//f64 serialization
vec pack109::serialize(f64 item) {
  vec bytes;
  u64* f64Item = (u64*) (&item);
  bytes.push_back(PACK109_F64);
  for(int i= 7; i>=0;i--) {
    u64 shifted = *f64Item  >> (8 * i);
    bytes.push_back((u8) shifted & 0x00000000000000FF);
  }
  return bytes;
}

//f64 deserialize
f64 pack109::deserialize_f64(vec bytes) {
  u64 result = 0;
  if(bytes[0] == PACK109_F64) {
    int posOfByte = 1;
    for(int i=7; i>=0; i--) {
      u64 shifted = (u64)(bytes[posOfByte]) << (8*i);
      result = result | shifted;
      posOfByte++;
    }
    f64 *f64Pointer = (f64*) (&result);
    return *f64Pointer;
  }
  else {
    throw;
  }
}

//serialize strings
vec pack109::serialize(string item) {
  vec bytes;
  //s8 string
  if(item.size() < 256) {
    //tag
    bytes.push_back(PACK109_S8);
    //number of characters
    bytes.push_back((u8)item.size());
    //add each character to the vector
    for(int i=0; i<item.size(); i++) {
      bytes.push_back(item[i]);
    }
  }
  //s16 string
  else if(item.size() < 65536) {
    //tag
    bytes.push_back(PACK109_S16);
    u32 stringLength = (u32)item.size();
    bytes.push_back((u8)(stringLength >> 8));
    bytes.push_back((u8)(stringLength));
    for(int i=0; i<item.size(); i++) {
      bytes.push_back((u8)item[i]);
    }
  } 
  else {
    throw;
  }
  return bytes; 
}

//deserialize strings
string pack109::deserialize_string(vec bytes) {
  string result = ""; 
  if(bytes[0] == PACK109_S8) {
    for(int i=2; i< (bytes[1]+2); i++) {
      result += bytes[i]; 
    }
  }
  else if(bytes[0] == PACK109_S16) {
    int length = (bytes[1] << 8) | bytes[2];
    for(int i=3; i< (length+3); i++) {
      result += bytes[i]; 
    }
  }
  return result;
}

//serialize vector <u8>
vec pack109::serialize(std::vector<u8> item) {
  vec bytes;
  if(item.size() < 256) {
    bytes.push_back(PACK109_A8);
    bytes.push_back((u8)item.size());
    for(int i=0; i<item.size(); i++) {
      vec element = serialize(item[i]);
      for(int j=0; j<element.size(); j++) {
        bytes.push_back(element[j]);
      }
    }
  }
  else if (item.size() < 65536) {
    bytes.push_back(PACK109_A16);
    u32 stringLength = (u32)item.size();
    bytes.push_back((u8)(stringLength >> 8));
    bytes.push_back((u8)(stringLength));
    for(int i=0; i<item.size(); i++) {
      vec element = serialize(item[i]);
      for(int j=0; j<element.size(); j++) {
        bytes.push_back(element[j]);
      }
    }
  }
  return bytes;
}

//https://www.geeksforgeeks.org/slicing-a-vector-in-c/#:~:text=Slicing%20a%20vector%20means%20to,Y%20in%20a%20given%20vector.
// Function to slice a given vector
// from range X to Y
vec slicing(vec &arr, int x, int y) {
  // Starting and Ending iterators
  auto start = arr.begin() + x;
  auto end = arr.begin() + y + 1;

  //To store the sliced vector
  vec result(y-x+1);

  //Copy vector using copy function()
  copy(start, end, result.begin());

  // Return the final sliced vector
  return result;
}

//deserialize vector <u8>
std::vector<u8> pack109::deserialize_vec_u8(vec bytes) {
  std::vector<u8> result;
  if(bytes[0] == PACK109_A8) {
    for(int i= 2; i <(bytes[1]*2)+2; i +=2) {
      u8 element = deserialize_u8(slicing(bytes,i,i+2));
      result.push_back(element);
    }
  }
  else if(bytes[0] == PACK109_A16) {
    int bytesLength = 2 * (int)((bytes[1] << 8) | bytes[2]);
    for(int i = 2; i < bytesLength+2; i+=2) {
      u8 element = deserialize_u8(slicing(bytes, i+1, i+2));
      result.push_back(element);
    }
  }
  return result;
}

//serialize vector<u64>
vec pack109::serialize(std::vector<u64> item) {
  vec bytes;
  if(item.size() < 256) {
    bytes.push_back(PACK109_A8);
    bytes.push_back((u8)item.size());
    for(int i=0; i<item.size(); i++) {
      vec element = serialize(item[i]);
      for(int j=0; j<element.size(); j++) {
        bytes.push_back(element[j]);
      }
    }
  }
  else if(item.size() < 65536) {
    bytes.push_back(PACK109_A16);
    u32 stringLength = (u32)item.size();
    bytes.push_back((u8)(stringLength >> 8));
    bytes.push_back((u8)(stringLength));
    for(int i=0; i<item.size(); i++) {
      vec element = serialize(item[i]);
      for(int j=0; j<element.size(); j++) {
        bytes.push_back(element[j]);
      }
    }
  }
  return bytes;
}

//deserialize vector<u64>
std::vector<u64> pack109::deserialize_vec_u64(vec bytes) {
  std::vector<u64> result;
  if(bytes[0] == PACK109_A8) {
    for(int i= 2; i <(bytes[1]*9)+2; i +=9) {
      u64 element = deserialize_u64(slicing(bytes,i,i+9));
      result.push_back(element);
    }
  }
  else if(bytes[0] == PACK109_A16) {
    int bytesLength = 9 * (int)((bytes[1] << 8) | bytes[2]);
    for(int i = 2; i < bytesLength+2; i+=9) {
      u64 element = deserialize_u64(slicing(bytes, i+1, i+9));
      result.push_back(element);
    }
  }
  return result;
}

//serialize vector f64
vec pack109::serialize(std::vector<f64> item) {
  vec bytes;
  if(item.size() < 256) {
    bytes.push_back(PACK109_A8);
    bytes.push_back((u8)item.size());
    for(int i=0; i<item.size(); i++) {
      vec element = serialize(item[i]);
      for(int j=0; j<element.size(); j++) {
        bytes.push_back(element[j]);
      }
    }
  }
  else if(item.size() < 65536) {
    bytes.push_back(PACK109_A16);
    u32 stringLength = (u32)item.size();
    bytes.push_back((u8)(stringLength >> 8));
    bytes.push_back((u8)(stringLength));
    for(int i=0; i<item.size(); i++) {
      vec element = serialize(item[i]);
      for(int j=0; j<element.size(); j++) {
        bytes.push_back(element[j]);
      }
    }
  }
  return bytes;
}

//deserialize f64
std::vector<f64> pack109::deserialize_vec_f64(vec bytes) {
  std::vector<f64> result;
  if(bytes[0] == PACK109_A8) {
    for(int i= 2; i <(bytes[1]*9)+2; i +=9) {
      f64 element = deserialize_f64(slicing(bytes,i,i+9));
      result.push_back(element);
    }
  }
  else if(bytes[0] == PACK109_A16) {
    int bytesLength = 9 * (int)((bytes[1] << 8) | bytes[2]);
    for(int i = 2; i < bytesLength+2; i+=9) {
      f64 element = deserialize_f64(slicing(bytes, i+1, i+9));
      result.push_back(element);
    }
  }
  return result;
}

//seriliaze vector <string>
vec pack109::serialize(std::vector<string> item) {
  vec bytes;
  if(item.size() < 256) {
    bytes.push_back(PACK109_A8);
    bytes.push_back((u8)item.size());
    for(int i=0; i<item.size(); i++) {
      vec element = serialize(item[i]);
      for(int j=0; j<element.size(); j++) {
        bytes.push_back(element[j]);
      }
    }
  }
  else if (item.size() < 65536) {
    bytes.push_back(PACK109_A16);
    u32 stringLength = (u32)item.size();
    bytes.push_back((u8)(stringLength >> 8));
    bytes.push_back((u8)(stringLength));
    for(int i=0; i<item.size(); i++) {
      vec element = serialize(item[i]);
      for(int j=0; j<element.size(); j++) {
        bytes.push_back(element[j]);
      }
    }
  }
  return bytes;
}

//deserialize string
std::vector<string> pack109::deserialize_vec_string(vec bytes) {
  std::vector<string> result;
  if(bytes[0] == PACK109_A8) {
    for(int i= 2; i <(bytes[1]*2)+9; i +=2) {
      string element = deserialize_string(slicing(bytes,i,i+9));
      result.push_back(element);
    }
  }
  else if(bytes[0] == PACK109_A16) {
    int bytesLength = 9 * (int)((bytes[1] << 8) | bytes[2]);
    for(int i = 2; i < bytesLength+2; i+=2) {
      string element = deserialize_string(slicing(bytes, i+1, i+9));
      result.push_back(element);
    }
  }
  return result;
}

//method for pushing bytes to the original bytes vector
void pushBytes(vec *ogVec, vec addBytes) {
  for(int i=0; i<addBytes.size(); i++) {
    ogVec->push_back(addBytes[i]);
  }
}

//serialize struct File object
vec pack109::serialize(struct File item) {
  vec bytes;

  //add tag M16
  bytes.push_back(PACK109_M8);  
  //1 k/v pair
  bytes.push_back(0x1);  
  
  //serialize Key
  string fileString = "File";
  vec fileKey = serialize(fileString);
  pushBytes(&bytes, fileKey);
  
  //2 kv
  bytes.push_back(PACK109_M8); 
  bytes.push_back(0x02);
  
  //name key/value
  string nameString = "name";
  vec nameKey = serialize(nameString);
  pushBytes(&bytes, nameKey);

  //name value
  vec nameValue = serialize(item.name);
  pushBytes(&bytes, nameValue);
 
  //bytes key
  string bytesString = "bytes";
  vec bytesKey = serialize(bytesString);
  pushBytes(&bytes, bytesKey);
  
  //bytes value
  vec bytesSerialized = serialize(item.bytes);
  pushBytes(&bytes, bytesSerialized);
  
  return bytes;
}

//deserialize struct File objects
struct File pack109::deserialize_file(vec bytes) {
  vec type = slicing(bytes,2,7);
  string typeValue = deserialize_string(type);
  u8 length = bytes[17]; 
  u8 startName = 16; //so that the tag can be included
  u8 endName = (length + startName) + 1;  //since we started length at 17 to exclude tag
  vec nameSection = slicing(bytes,startName, endName);
  string fileName = deserialize_string(nameSection);
  u8 startBytes = (int)endName + 8; //skip bytes and its tags
  u8 endBytes = bytes.size()-1;
  vec bytesSection = slicing(bytes, startBytes, endBytes);
  vec fileBytes = deserialize_vec_u8(bytesSection);
  
  //create new file
  struct File newFile;
  newFile.name = fileName;
  newFile.bytes = fileBytes;
  return newFile;
}

//deserialize file request
struct File pack109::deserialize_fileRequest(vec bytes) {
  struct File requestedFile;

  //extract the name of the file
  vec nameSection = slicing(bytes,19, bytes.size()-1);
  string fileName = deserialize_string(nameSection);

  //recreate the struct with a name only
  requestedFile.name = fileName;
  return requestedFile;
}

//checkType (confirms if its a file or not)
bool pack109::isFile(vec bytes) {
  vec type = slicing(bytes,2,7);
  string typeValue = deserialize_string(type);
  if(typeValue=="File") {
    return true;
  }
  return false;
}

//printVec function
void pack109::printVec(vec &bytes){
  printf("[ ");
  for (int i = 0; i < bytes.size(); i++){
    printf("%x ", bytes[i]);
  }
  printf("]\n");
}