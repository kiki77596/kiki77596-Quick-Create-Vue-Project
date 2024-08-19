#include"C_VueCommand.h"
static void Print(string st, bool isendl = true)
{
    if (isendl)
        std::cout << st << std::endl;
    else
        std::cout << st;
}
void C_VueCommand::Run()
{
    auto GetCurrentPath = []()->string {
        return std::filesystem::current_path().string();
        };
    Print("當前所在目錄: " + GetCurrentPath());

    Print("是否建一次創建複數專案?", false);
    bool cr;
    std::cin >> cr;
    if (cr)
        CreateMultipleProject();
    else
        CreateSingleProject();
}

string C_VueCommand::exce(const std::string& cmd)
{
    std::array<char, 128Ui64> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(cmd.c_str(), "r"), _pclose);
    if (!pipe) throw std::runtime_error("popen() failed!");
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

void C_VueCommand::CreateMultipleProject()
{
    Print("欲創建專案上限? ");
    int amount = 0;
    std::cin >> amount;
    std::queue<string> multiple;
    for (int i = 1; i <= amount; i++)
    {
        multiple.push("0" + to_string(i));
    }
    Process(multiple);
}

void C_VueCommand::CreateSingleProject()
{
    Print("輸入欲創建專案名稱: ");
    string project_name;
    std::cin >> project_name;
    Process(project_name);
}

void C_VueCommand::Process(string& project_name)
{
    string command = "npm init vue@latest " + project_name;
    string command_0 = "cd " + project_name + " && npm install && npm run dev";
    system(command.c_str());
    CreateRunBat(project_name);
    system(command_0.c_str());
}

void C_VueCommand::Process(std::queue<string>& project_name)
{

    bool IsProcesEnd = true;

    while (!project_name.empty())
    {
        string command = "npm init vue@latest " + project_name.front();

        system(command.c_str());
        string command_0 = "cd " + project_name.front() + "&& npm install";
        system(command_0.c_str());
        project_name.pop();
        CreateRunBat(project_name.front());
    }
}

void C_VueCommand::CreateRunBat(string& project_name)
{
    std::string bat_file_name = project_name  + "/Start Up.bat";
    std::ofstream bat_file(bat_file_name);
    if (bat_file.is_open()) {
        bat_file << "@echo off\n";
        bat_file << "cd " << project_name << "\n";
        bat_file << "npm run dev \n";
        bat_file << "endlocal\n";
        bat_file.close();
        std::cout << "生成批處理文件: " << bat_file_name << std::endl;
    }
    else {
        std::cerr << "無法創建批處理文件: " << bat_file_name << std::endl;
    }
}

string C_VueCommand::GetURL()
{

    return string();
}
