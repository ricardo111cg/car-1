#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <ctime>
#include <cstdlib>

using namespace std;

// ������ɱ��
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

// ��̥��
class Tire {
public:
    string type;
    int size;

    void setType(const string& new_type) { type = new_type; }
    void setSize(int new_size) { size = new_size; }

    void print() const {
        cout << "��̥����: " << type << ", �ߴ�: " << size << "mm" << endl;
    }

    void saveToFile(ofstream& file) const {
        file << type << endl;
        file << size << endl;
    }

    void loadFromFile(ifstream& file) {
        getline(file, type);
        file >> size;
        file.ignore(); // ���Ի��з�
    }
};

// ������
class Chassis {
public:
    string id;
    string model = "SCOUT MINI";
    int wheelbase = 451;
    int tread = 490;
    int minGroundClearance = 115;
    float minTurningRadius = 0;
    string driveType = "��������";
    int maxTravelDistance = 10 * 1000; // ��λת��Ϊ��
    vector<Tire> tires;

    Chassis() {
        id = "dp" + generateId(8);
        tires.push_back(Tire{"��·��", 175});
        tires.push_back(Tire{"�����ķ��", 175});
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
        cout << "���̱��: " << id << endl;
        cout << "�ͺ�: " << model << endl;
        cout << "���: " << wheelbase << "mm" << endl;
        cout << "�־�: " << tread << "mm" << endl;
        cout << "��С��ؼ�϶: " << minGroundClearance << "mm" << endl;
        cout << "��Сת��뾶: " << minTurningRadius << "m" << endl;
        cout << "������ʽ: " << driveType << endl;
        cout << "����г�: " << maxTravelDistance / 1000 << "km" << endl;
        cout << "��̥:" << endl;
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
        file.ignore(); // ���Ի��з�
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

// AGX�׼���
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
        cout << "�ͺ�: " << model << endl;
        cout << "AI����: " << aiPerformance << "TOPS" << endl;
        cout << "CUDA����: " << cudaCores << endl;
        cout << "Tensor����: " << tensorCores << endl;
        cout << "�Դ�: " << vram << "GB" << endl;
        cout << "�洢: " << storage << "GB" << endl;
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
        file.ignore(); // ���Ի��з�
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

// ˫Ŀ����ͷ��
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
        cout << "�ͺ�: " << model << endl;
        cout << "����ͷ����: " << cameraType << endl;
        cout << "RGB֡�ֱ���: " << resolution.first << "x" << resolution.second << endl;
        cout << "RGB֡��: " << frameRate << "fps" << endl;
        cout << "FOV: " << fov.first << "x" << fov.second << "��" << endl;
        cout << "���֡��: " << depthFrameRate << "fps" << endl;
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

// 9����������
class Gyroscope {
public:
    string model = "CH110";
    string manufacturer = "NXP";

    void setModel(const string& new_model) { model = new_model; }
    void setManufacturer(const string& new_manufacturer) { manufacturer = new_manufacturer; }

    void print() const {
        cout << "�ͺ�: " << model << endl;
        cout << "����: " << manufacturer << endl;
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

// ���߼����״���
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
        cout << "�ͺ�: " << model << endl;
        cout << "ͨ����: " << channels << endl;
        cout << "���Է�Χ: " << testRange << "m" << endl;
        cout << "����: " << powerConsumption << "W" << endl;
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

// Һ����ʾ����
class LCD {
public:
    double size = 11.6;
    string model = "super";

    void setSize(double new_size) { size = new_size; }
    void setModel(const string& new_model) { model = new_model; }

    void print() const {
        cout << "�ߴ�: " << size << "Ӣ��" << endl;
        cout << "�ͺ�: " << model << endl;
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

// ���ģ����
class BatteryModule {
public:
    string parameters = "24V/15Ah";
    string externalPower = "24V";
    double chargeTime = 2;

    void setParameters(const string& new_parameters) { parameters = new_parameters; }
    void setExternalPower(const string& new_externalPower) { externalPower = new_externalPower; }
    void setChargeTime(double new_chargeTime) { chargeTime = new_chargeTime; }

    void print() const {
        cout << "����: " << parameters << endl;
        cout << "���⹩��: " << externalPower << endl;
        cout << "���ʱ��: " << chargeTime << "Сʱ" << endl;
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

// ѧ����Ϣ��
class StudentInfo {
public:
    string studentNumber;
    string name;

    void setStudentNumber(const string& new_studentNumber) { studentNumber = new_studentNumber; }
    void setName(const string& new_name) { name = new_name; }

    void print() const {
        cout << "ѧ��: " << studentNumber << endl;
        cout << "����: " << name << endl;
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

// ����С����
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
        cout << "����С�����: " << id << endl;
        cout << "������Ϣ:" << endl;
        chassis.print();
        cout << "AGX�׼���Ϣ:" << endl;
        agxKit.print();
        cout << "˫Ŀ����ͷ��Ϣ:" << endl;
        stereoCamera.print();
        cout << "���߼����״���Ϣ:" << endl;
        laserRadar.print();
        cout << "9����������Ϣ:" << endl;
        gyroscope.print();
        cout << "Һ����ʾ����Ϣ:" << endl;
        lcd.print();
        cout << "���ģ����Ϣ:" << endl;
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

// ������
int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    vector<SmartCar> cars;
    vector<StudentInfo> students;

    // ��������������С��
    for (int i = 0; i < 10; ++i) {
        SmartCar car;
        cars.push_back(car);
        
        // ����ѧ����Ϣ
        StudentInfo student;
        student.setStudentNumber(to_string(i + 1));
        student.setName("ѧ��" + to_string(i + 1));
        students.push_back(student);
    }

    // ������Ϣ���ļ�
    ofstream outFile("smart_cars_info.txt");
    for (size_t i = 0; i < cars.size(); ++i) {
        cars[i].saveToFile(outFile);
        students[i].saveToFile(outFile);
    }
    outFile.close();

    // ���ļ�������Ϣ����ʾ
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

        cout << "����С����Ϣ:" << endl;
        loadedCar.print();
        cout << "�����ѧ����Ϣ:" << endl;
        loadedStudent.print();

        cout << "��'n'��ʾ��һ��С����Ϣ����'p'��ʾ��һ��С����Ϣ��" << endl;
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