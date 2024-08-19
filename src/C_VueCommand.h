#pragma once
#include"../Library/bits/stdc++.h"
#include <iostream>
#include <queue>
#include <string>
#include <fstream>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>
#include<filesystem>
using namespace std;
class C_VueCommand
{
public:
    C_VueCommand() = default;
    void Run();
private:
    string exce(const std::string& cmd);
    void CreateMultipleProject();
    void CreateSingleProject();
    void Process(string& project_name);
    void Process(std::queue<string>& project_name);
    void CreateRunBat(string& project_name);
    string GetURL();
};