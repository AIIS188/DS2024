#include <iostream>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <memory>
#include "D:\\DS24\\DS24\\exp3\\BinTree.h"
#include "D:\\DS24\\DS24\\Template class\\Huffman.h"

#define N_CHAR (0x80 - 0x20)

using namespace std;

// ���� statistics �����Ķ��壺ͳ���ļ���ÿ���ַ���Ƶ��
int* statistics(const char* filePath) {
    int* freq = new int[N_CHAR]();  // ��ʼ��Ƶ������
    ifstream file(filePath);
    if (!file) {
        cerr << "�޷����ļ�: " << filePath << endl;
        return nullptr;
    }

    char ch;
    while (file.get(ch)) {
        if (ch >= 0x20 && ch < 0x80) {  // ����ַ��Ƿ�����Ч��Χ��
            freq[ch - 0x20]++;          // ����Ƶ��
        }
    }

    file.close();
    return freq;
}

// ������
int main() {
    // 1. ͳ���ַ�Ƶ��
    char* sample_text_file = "sample.txt";
    int* freq = statistics(sample_text_file);
    if (!freq) {
        cerr << "�ַ�Ƶ��ͳ��ʧ�ܡ�" << endl;
        return 1;
    }

    // 2. ��ʼ�� Huffman ɭ��
    HuffForest* forest = initForest(freq);
    if (!forest) {
        cerr << "Huffman ɭ�ֳ�ʼ��ʧ�ܡ�" << endl;
        delete[] freq;
        return 1;
    }

    // 3. ���� Huffman ��
    HuffTree* huffmanTree = generateTree(forest);
    if (!huffmanTree) {
        cerr << "Huffman ������ʧ�ܡ�" << endl;
        delete[] freq;
        delete forest;
        return 1;
    }

    cout << "Huffman Tree generated for the input text." << endl;

    // 4. ʾ������
    HuffCode code;
    code.set(0);  // ʾ������
    code.set(1);  // ʾ������
    int n = code.size();

    cout << "Decoding result: ";
    decode(huffmanTree, &code, n);  // ���� decode �������������������
    cout << endl;

    // 5. �����ڴ�
    delete[] freq;
    delete forest;
    delete huffmanTree;

    return 0;
}
