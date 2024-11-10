#include <iostream>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <memory>
#include "D:\\DS24\\DS24\\exp3\\BinTree.h"
#include "D:\\DS24\\DS24\\Template class\\Huffman.h"

#define N_CHAR (0x80 - 0x20)

using namespace std;

// 假设 statistics 函数的定义：统计文件中每个字符的频率
int* statistics(const char* filePath) {
    int* freq = new int[N_CHAR]();  // 初始化频率数组
    ifstream file(filePath);
    if (!file) {
        cerr << "无法打开文件: " << filePath << endl;
        return nullptr;
    }

    char ch;
    while (file.get(ch)) {
        if (ch >= 0x20 && ch < 0x80) {  // 检查字符是否在有效范围内
            freq[ch - 0x20]++;          // 更新频率
        }
    }

    file.close();
    return freq;
}

// 主函数
int main() {
    // 1. 统计字符频率
    char* sample_text_file = "sample.txt";
    int* freq = statistics(sample_text_file);
    if (!freq) {
        cerr << "字符频率统计失败。" << endl;
        return 1;
    }

    // 2. 初始化 Huffman 森林
    HuffForest* forest = initForest(freq);
    if (!forest) {
        cerr << "Huffman 森林初始化失败。" << endl;
        delete[] freq;
        return 1;
    }

    // 3. 生成 Huffman 树
    HuffTree* huffmanTree = generateTree(forest);
    if (!huffmanTree) {
        cerr << "Huffman 树生成失败。" << endl;
        delete[] freq;
        delete forest;
        return 1;
    }

    cout << "Huffman Tree generated for the input text." << endl;

    // 4. 示例解码
    HuffCode code;
    code.set(0);  // 示例编码
    code.set(1);  // 示例编码
    int n = code.size();

    cout << "Decoding result: ";
    decode(huffmanTree, &code, n);  // 假设 decode 函数定义了输出解码结果
    cout << endl;

    // 5. 清理内存
    delete[] freq;
    delete forest;
    delete huffmanTree;

    return 0;
}
