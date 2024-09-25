#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <ctime>
#include <cstdlib>

using namespace std;

// 随机生成编号
string generateId(int length) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string tmp(length, ' ');
    for (int i = 0; i < length; ++i) {
        tmp[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    return tmp;
}

// 轮胎类
class Tire {
public:
    string type;
    int size;

    void setType(const string& new_type) { type = new_type; }
    void setSize(int new_size) { size = new_size; }

    void print() const {
        cout << "轮胎类型: " << type << ", 尺寸: " << size << "mm" << endl;
    }

    void saveToFile(ofstream& file) const {
        file << type << endl;
        file << size << endl;
    }

    void loadFromFile(ifstream& file) {
        getline(file, type);
        file >> size;
        file.ignore(); // 忽略换行符
    }
};

// 底盘类
class Chassis {
public:
    string id;
    string model = "SCOUT MINI";
    int wheelbase = 451;
    int tread = 490;
    int minGroundClearance = 115;
    float minTurningRadius = 0;
    string driveType = "四轮四驱";
    int maxTravelDistance = 10 * 1000; // 单位转换为米
    vector<Tire> tires;

    Chassis() {
        id = "dp" + generateId(8);
        tires.push_back(Tire{"公路轮", 175});
        tires.push_back(Tire{"麦克纳姆轮", 175});
    }

    void setId(const string& new_id) { id = new_id; }
    void setModel(const string& new_model) { model = new_model; }
    void setWheelbase(int new_wheelbase) { wheelbase = new_wheelbase; }
    void setTread(int new_tread) { tread = new_tread; }
    void setMinGroundClearance(int new_minGroundClearance) { minGroundClearance = new_minGroundClearance; }
    void setMinTurningRadius(float new_minTurningRadius) { minTurningRadius = new_minTurningRadius; }
    void setDriveType(const string& new_driveType) { driveType = new_driveType; }
    void setMaxTravelDistance(int new_maxTravelDistance) { maxTravelDistance = new_maxTravelDistance; }

    void print() const {
        cout << "底盘编号: " << id << endl;
        cout << "型号: " << model << endl;
        cout << "轴距: " << wheelbase << "mm" << endl;
        cout << "轮距: " << tread << "mm" << endl;
        cout << "最小离地间隙: " << minGroundClearance << "mm" << endl;
        cout << "最小转弯半径: " << minTurningRadius << "m" << endl;
        cout << "驱动形式: " << driveType << endl;
        cout << "最大行程: " << maxTravelDistance / 1000 << "km" << endl;
        cout << "轮胎:" << endl;
        for (const auto& tire : tires) {
            tire.print();
        }
    }

    void saveToFile(ofstream& file) const {
        file << id << endl;
        file << model << endl;
        file << wheelbase << endl;
        file << tread << endl;
        file << minGroundClearance << endl;
        file << minTurningRadius << endl;
        file << driveType << endl;
        file << maxTravelDistance << endl;
        file << tires.size() << endl;
        for (const auto& tire : tires) {
            tire.saveToFile(file);
        }
    }

    void loadFromFile(ifstream& file) {
        getline(file, id);
        getline(file, model);
        file >> wheelbase;
        file.ignore(); // 忽略换行符
        file >> tread;
        file.ignore();
        file >> minGroundClearance;
        file.ignore();
        file >> minTurningRadius;
        file.ignore();
        getline(file, driveType);
        file >> maxTravelDistance;
        file.ignore();
        int numTires;
        file >> numTires;
        file.ignore();
        tires.resize(numTires);
        for (auto& tire : tires) {
            tire.loadFromFile(file);
        }
    }
};

// AGX套件类
class AGXKit {
public:
    string model = "AGX Xavier";
    double aiPerformance = 32; // TOPS
    int cudaCores = 512;
    int tensorCores = 64;
    int vram = 32; // GB
    int storage = 32; // GB

    void setModel(const string& new_model) { model = new_model; }
    void setAIPerformance(double new_aiPerformance) { aiPerformance = new_aiPerformance; }
    void setCudaCores(int new_cudaCores) { cudaCores = new_cudaCores; }
    void setTensorCores(int new_tensorCores) { tensorCores = new_tensorCores; }
    void setVRAM(int new_vram) { vram = new_vram; }
    void setStorage(int new_storage) { storage = new_storage; }

    void print() const {
        cout << "型号: " << model << endl;
        cout << "AI性能: " << aiPerformance << "TOPS" << endl;
        cout << "CUDA核心: " << cudaCores << endl;
        cout << "Tensor核心: " << tensorCores << endl;
        cout << "显存: " << vram << "GB" << endl;
        cout << "存储: " << storage << "GB" << endl;
    }

    void saveToFile(ofstream& file) const {
        file << model << endl;
        file << aiPerformance << endl;
        file << cudaCores << endl;
        file << tensorCores << endl;
        file << vram << endl;
        file << storage << endl;
    }

    void loadFromFile(ifstream& file) {
        getline(file, model);
        file >> aiPerformance;
        file.ignore(); // 忽略换行符
        file >> cudaCores;
        file.ignore();
        file >> tensorCores;
        file.ignore();
        file >> vram;
        file.ignore();
        file >> storage;
        file.ignore();
    }
};

// 双目摄像头类
class StereoCamera {
public:
    string model = "RealSense D435i";
    string cameraType = "D430";
    pair<int, int> resolution = {1920, 1080};
    int frameRate = 30;
    pair<int, int> fov = {87, 58};
    int depthFrameRate = 90;

    void setModel(const string& new_model) { model = new_model; }
    void setCameraType(const string& new_cameraType) { cameraType = new_cameraType; }
    void setResolution(pair<int, int> new_resolution) { resolution = new_resolution; }
    void setFrameRate(int new_frameRate) { frameRate = new_frameRate; }
    void setFOV(pair<int, int> new_fov) { fov = new_fov; }
    void setDepthFrameRate(int new_depthFrameRate) { depthFrameRate = new_depthFrameRate; }

    void print() const {
        cout << "型号: " << model << endl;
        cout << "摄像头类型: " << cameraType << endl;
        cout << "RGB帧分辨率: " << resolution.first << "x" << resolution.second << endl;
        cout << "RGB帧率: " << frameRate << "fps" << endl;
        cout << "FOV: " << fov.first << "x" << fov.second << "°" << endl;
        cout << "深度帧率: " << depthFrameRate << "fps" << endl;
    }

    void saveToFile(ofstream& file) const {
        file << model << endl;
        file << cameraType << endl;
        file << resolution.first << " " << resolution.second << endl;
        file << frameRate << endl;
        file << fov.first << " " << fov.second << endl;
        file << depthFrameRate << endl;
    }

    void loadFromFile(ifstream& file) {
        getline(file, model);
        getline(file, cameraType);
        int w, h;
        file >> w >> h;
        file.ignore();
        file >> frameRate;
        file.ignore();
        int x, y;
        file >> x >> y;
        file.ignore();
        file >> depthFrameRate;
        file.ignore();
        resolution = {w, h};
        fov = {x, y};
    }
};

// 9轴陀螺仪类
class Gyroscope {
public:
    string model = "CH110";
    string manufacturer = "NXP";

    void setModel(const string& new_model) { model = new_model; }
    void setManufacturer(const string& new_manufacturer) { manufacturer = new_manufacturer; }

    void print() const {
        cout << "型号: " << model << endl;
        cout << "厂家: " << manufacturer << endl;
    }

    void saveToFile(ofstream& file) const {
        file << model << endl;
        file << manufacturer << endl;
    }

    void loadFromFile(ifstream& file) {
        getline(file, model);
        getline(file, manufacturer);
    }
};

// 多线激光雷达类
class LaserRadar {
public:
    string model = "RS-Helios-16p";
    int channels = 16;
    int testRange = 100;
    double powerConsumption = 8;

    void setModel(const string& new_model) { model = new_model; }
    void setChannels(int new_channels) { channels = new_channels; }
    void setTestRange(int new_testRange) { testRange = new_testRange; }
    void setPowerConsumption(double new_powerConsumption) { powerConsumption = new_powerConsumption; }

    void print() const {
        cout << "型号: " << model << endl;
        cout << "通道数: " << channels << endl;
        cout << "测试范围: " << testRange << "m" << endl;
        cout << "功耗: " << powerConsumption << "W" << endl;
    }

    void saveToFile(ofstream& file) const {
        file << model << endl;
        file << channels << endl;
        file << testRange << endl;
        file << powerConsumption << endl;
    }

    void loadFromFile(ifstream& file) {
        getline(file, model);
        file >> channels;
        file.ignore();
        file >> testRange;
        file.ignore();
        file >> powerConsumption;
        file.ignore();
    }
};

// 液晶显示屏类
class LCD {
public:
    double size = 11.6;
    string model = "super";

    void setSize(double new_size) { size = new_size; }
    void setModel(const string& new_model) { model = new_model; }

    void print() const {
        cout << "尺寸: " << size << "英寸" << endl;
        cout << "型号: " << model << endl;
    }

    void saveToFile(ofstream& file) const {
        file << size << endl;
        file << model << endl;
    }

    void loadFromFile(ifstream& file) {
        file >> size;
        file.ignore();
        getline(file, model);
    }
};

// 电池模块类
class BatteryModule {
public:
    string parameters = "24V/15Ah";
    string externalPower = "24V";
    double chargeTime = 2;

    void setParameters(const string& new_parameters) { parameters = new_parameters; }
    void setExternalPower(const string& new_externalPower) { externalPower = new_externalPower; }
    void setChargeTime(double new_chargeTime) { chargeTime = new_chargeTime; }

    void print() const {
        cout << "参数: " << parameters << endl;
        cout << "对外供电: " << externalPower << endl;
        cout << "充电时长: " << chargeTime << "小时" << endl;
    }

    void saveToFile(ofstream& file) const {
        file << parameters << endl;
        file << externalPower << endl;
        file << chargeTime << endl;
    }

    void loadFromFile(ifstream& file) {
        getline(file, parameters);
        getline(file, externalPower);
        file >> chargeTime;
        file.ignore();
    }
};

// 学生信息类
class StudentInfo {
public:
    string studentNumber;
    string name;

    void setStudentNumber(const string& new_studentNumber) { studentNumber = new_studentNumber; }
    void setName(const string& new_name) { name = new_name; }

    void print() const {
        cout << "学号: " << studentNumber << endl;
        cout << "姓名: " << name << endl;
    }

    void saveToFile(ofstream& file) const {
        file << studentNumber << endl;
        file << name << endl;
    }

    void loadFromFile(ifstream& file) {
        getline(file, studentNumber);
        getline(file, name);
    }
};

// 智能小车类
class SmartCar {
public:
    string id;
    Chassis chassis;
    AGXKit agxKit;
    StereoCamera stereoCamera;
    LaserRadar laserRadar;
    Gyroscope gyroscope;
    LCD lcd;
    BatteryModule batteryModule;

    SmartCar() {
        id = "cqusn" + generateId(16);
    }

    void setID(const string& new_id) { id = new_id; }

    void print() const {
        cout << "智能小车编号: " << id << endl;
        cout << "底盘信息:" << endl;
        chassis.print();
        cout << "AGX套件信息:" << endl;
        agxKit.print();
        cout << "双目摄像头信息:" << endl;
        stereoCamera.print();
        cout << "多线激光雷达信息:" << endl;
        laserRadar.print();
        cout << "9轴陀螺仪信息:" << endl;
        gyroscope.print();
        cout << "液晶显示屏信息:" << endl;
        lcd.print();
        cout << "电池模块信息:" << endl;
        batteryModule.print();
    }

    void saveToFile(ofstream& file) const {
        file << id << endl;
        chassis.saveToFile(file);
        agxKit.saveToFile(file);
        stereoCamera.saveToFile(file);
        laserRadar.saveToFile(file);
        gyroscope.saveToFile(file);
        lcd.saveToFile(file);
        batteryModule.saveToFile(file);
    }

    void loadFromFile(ifstream& file) {
        getline(file, id);
        chassis.loadFromFile(file);
        agxKit.loadFromFile(file);
        stereoCamera.loadFromFile(file);
        laserRadar.loadFromFile(file);
        gyroscope.loadFromFile(file);
        lcd.loadFromFile(file);
        batteryModule.loadFromFile(file);
    }
};

// 主函数
int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    vector<SmartCar> cars;
    vector<StudentInfo> students;

    // 创建并设置智能小车
    for (int i = 0; i < 10; ++i) {
        SmartCar car;
        cars.push_back(car);
        
        // 分配学生信息
        StudentInfo student;
        student.setStudentNumber(to_string(i + 1));
        student.setName("学生" + to_string(i + 1));
        students.push_back(student);
    }

    // 保存信息到文件
    ofstream outFile("smart_cars_info.txt");
    for (size_t i = 0; i < cars.size(); ++i) {
        cars[i].saveToFile(outFile);
        students[i].saveToFile(outFile);
    }
    outFile.close();

    // 从文件加载信息并显示
    ifstream inFile("smart_cars_info.txt");
    int index = 0;
    while (true) {
        if (!inFile) break;

        SmartCar loadedCar;
        inFile >> loadedCar.id;
        loadedCar.loadFromFile(inFile);

        StudentInfo loadedStudent;
        inFile >> loadedStudent.studentNumber;
        inFile >> loadedStudent.name;

        cout << "智能小车信息:" << endl;
        loadedCar.print();
        cout << "分配的学生信息:" << endl;
        loadedStudent.print();

        cout << "按'n'显示下一辆小车信息，按'p'显示上一辆小车信息：" << endl;
        char key;
        cin >> key;
        if (key == 'n') {
            ++index;
        } else if (key == 'p' && index > 0) {
            --index;
        }
        if (index >= cars.size() || index < 0) break;
    }

    return 0;
}