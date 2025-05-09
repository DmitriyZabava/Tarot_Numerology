#include <iostream>
#include <string>
#include <sstream>
#include <map>

using namespace std;

enum State {
    START,
    READ_INPUT,
    CALC_NAME_NUMBER,
    CALC_BIRTH_NUMBER,
    CALC_TOTAL_NUMBER,
    CALC_KARMIC_TAIL,
    PRINT_RESULTS,
    ERROR,
    END
};

int letToNum(char c) {
    c = tolower(c);
    if (c >= 'a' && c <= 'i') return c - 'a' + 1;
    if (c >= 'j' && c <= 'r') return c - 'j' + 1;
    if (c >= 's' && c <= 'z') return c - 's' + 1;
    return 0;
}

int toSingle(int num) {
    while (num > 9) {
        int sum = 0;
        while (num > 0) {
            sum += num % 10;
            num /= 10;
        }
        num = sum;
    }
    return num;
}

string getCharacteristic(int num) {
    map<int, string> characteristics = {
        {1, "1 - Лидерство, независимость"},
        {2, "2 - Партнерство, гармония"},
        {3, "3 - Творчество, самовыражение"},
        {4, "4 - Стабильность, трудолюбие"},
        {5, "5 - Перемены, приключения"},
        {6, "6 - Семья, забота"},
        {7, "7 - Духовность, анализ"},
        {8, "8 - Власть, материальный успех"},
        {9, "9 - Гуманизм, завершение"}
    };
    return characteristics.count(num) ? characteristics[num] : "Неизвестная характеристика";
}

string getTailDescription(int num) {
    map<int, string> tails = {
        {1, "легкомыслие, чрезмерная строгость. Наслаждайтесь каждым моментом."},
        {2, "манипулирование людьми, отсутствие воли. Уважайте чужое мнение, как свое."},
        {3, "непринятие женственности, проблемы с женщинами рода. Проработайте гордыню и скупость."},
        {4, "злоупотребление силой, подавление инициативы. Будьте мягче и щедрее."},
        {5, "злоупотребление властью, статусом. Соблюдайте закон, делитесь знаниями."},
        {6, "проблемы в любви, любовная магия. Стройте отношения вопреки страхам."},
        {7, "воплощение в образе воина, преграды на пути. Сдерживайте внутреннюю агрессию."},
        {8, "нарушение баланса, проблемы с детьми. Не обижайтесь на людей."},
        {9, "одиночество, презрение к глупцам. Избавьтесь от гордыни."},
        {10, "неумение жить своей жизнью, недостаток ответственности. Много работайте."},
        {11, "раздражение от чужой медлительности. Не гнобите других, реализуйте свой потенциал."},
        {12, "неумение служить, вынужденная жертва. Поверьте в то, что добро возвращается."},
        {13, "ранний уход из жизни, желание прожить долгую жизнь. Помогайте больным, старикам и немощным."},
        {14, "сомнение в своих талантах, страх зависимостей. Зарабатывайте на таланте."},
        {15, "раненое эго, проблемы в отношениях с миром. Помогайте людям, будьте независимы."},
        {16, "разрушения в прошлой и текущей жизни себя и других людей. Проработайте внутреннюю агрессию."},
        {17, "звездная болезнь, непризнание окружающими. Помогайте другим людям реализовать талант."},
        {18, "занятия магией, злоупотребление силой. Направьте потенциал на благо людям."},
        {19, "обман в благотворительности, потребность служить людям. Будьте щедрее."},
        {20, "плохие отношения с родителями, проблемы в семье. Примите близких такими, как есть."},
        {21, "занятие негативной деятельностью, искушение вредить людям. Будьте миротворцем."},
        {22, "зависимости любого рода, ревность. Будьте свободны и признайте свободу других людей."}
    };
    return tails.count(num) ? tails[num] : "неизвестное кармическое число.";
}

struct Tail {
    int bottom;
    int first;
    int second;
    int third;
};

Tail calculateTail(int day, int month, int year) {
    Tail result;
    
    // Calculate year sum
    int year_sum = 0;
    int temp = year;
    while (temp > 0) {
        year_sum += temp % 10;
        temp /= 10;
    }
    if (year_sum > 22) year_sum = toSingle(year_sum);
    
    // Bottom number
    result.bottom = day + month + year_sum;
    if (result.bottom > 22) result.bottom = toSingle(result.bottom);
    
    // Center number
    int center = day + month + year_sum + result.bottom;
    center = toSingle(center);
    
    // Karmic tail
    result.first = center + result.bottom;
    if (result.first > 22) result.first = toSingle(result.first);
    
    result.second = result.first + result.bottom;
    if (result.second > 22) result.second = toSingle(result.second);
    
    result.third = result.second + result.bottom;
    if (result.third > 22) result.third = toSingle(result.third);
    
    return result;
}

int main() {
    // Устанавливаем заголовок для вывода JSON
    cout << "Content-type: application/json\n\n";

    // Получаем данные из GET/POST запроса
    string query = getenv("QUERY_STRING");  // Для GET-запросов

    // Пример: name=Alexander&day=15&month=7&year=1990
    string name;
    int day = 0, month = 0, year = 0;

    // Парсим QUERY_STRING
    size_t name_pos = query.find("name=");
    size_t day_pos = query.find("&day=");
    size_t month_pos = query.find("&month=");
    size_t year_pos = query.find("&year=");

    if (name_pos == string::npos || day_pos == string::npos || 
        month_pos == string::npos || year_pos == string::npos) {
        cout << "{\"error\":\"Invalid query format. Expected: name=...&day=...&month=...&year=...\"}";
        return 1;
    }

    name = query.substr(name_pos + 5, day_pos - (name_pos + 5));
    day = stoi(query.substr(day_pos + 5, month_pos - (day_pos + 5)));
    month = stoi(query.substr(month_pos + 7, year_pos - (month_pos + 7)));
    year = stoi(query.substr(year_pos + 6));

    // Проверка данных
    if (day < 1 || day > 31 || month < 1 || month > 12 || year < 1000 || year > 9999) {
        cout << "{\"error\":\"Invalid date values\"}";
        return 1;
    }

    int nameNumber = 0;
    for (char c : name) {
        nameNumber += letToNum(c);
    }
    nameNumber = toSingle(nameNumber);

    int birthNumber = toSingle(day + month + toSingle(year));
    int totalNumber = toSingle(nameNumber + birthNumber);

    Tail tail = calculateTail(day, month, year);

    // Вывод JSON
    cout << "{";
    cout << "\"name_number\":{\"value\":" << nameNumber << ",\"characteristic\":\"" << getCharacteristic(nameNumber) << "\"},";
    cout << "\"birth_number\":{\"value\":" << birthNumber << ",\"characteristic\":\"" << getCharacteristic(birthNumber) << "\"},";
    cout << "\"total_number\":{\"value\":" << totalNumber << ",\"characteristic\":\"" << getCharacteristic(totalNumber) << "\"},";
    cout << "\"karmic_tail\":{";
    cout << "\"numbers\":[" << tail.first << "," << tail.second << "," << tail.third << "],";
    cout << "\"descriptions\":[";
    cout << "\"" << getTailDescription(tail.first) << "\",";
    cout << "\"" << getTailDescription(tail.second) << "\",";
    cout << "\"" << getTailDescription(tail.third) << "\"";
    cout << "]";
    cout << "}";
    cout << "}";
   
    return 0;
}