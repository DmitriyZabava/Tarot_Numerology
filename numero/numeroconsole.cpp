#include <iostream>
#include <string>
#include <sstream>

using namespace std;
enum State {
    START,
    READ_NAME,
    READ_DAY,
    READ_MONTH,
    READ_YEAR,
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

int toSingle (int num) {
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

void char1(int num) {
    switch(num) {
        case 1: cout << "1 - Лидерство, независимость"; break;
        case 2: cout << "2 - Партнерство, гармония"; break;
        case 3: cout << "3 - Творчество, самовыражение"; break;
        case 4: cout << "4 - Стабильность, трудолюбие"; break;
        case 5: cout << "5 - Перемены, приключения"; break;
        case 6: cout << "6 - Семья, забота"; break;
        case 7: cout << "7 - Духовность, анализ"; break;
        case 8: cout << "8 - Власть, материальный успех"; break;
        case 9: cout << "9 - Гуманизм, завершение"; break;
        default: cout << "Неизвестная характеристика";
    }
    cout << endl;
}

void printTail(int num) {
    cout << num << " -- ";
    switch(num) {
        case 1: cout << "легкомыслие, чрезмерная строгость. Наслаждайтесь каждым моментом."; break;
        case 2: cout << "манипулирование людьми, отсутствие воли. Уважайте чужое мнение, как свое."; break;
        case 3: cout << "непринятие женственности, проблемы с женщинами рода. Проработайте гордыню и скупость."; break;
        case 4: cout << "злоупотребление силой, подавление инициативы. Будьте мягче и щедрее."; break;
        case 5: cout << "злоупотребление властью, статусом. Соблюдайте закон, делитесь знаниями."; break;
        case 6: cout << "проблемы в любви, любовная магия. Стройте отношения вопреки страхам."; break;
        case 7: cout << "воплощение в образе воина, преграды на пути. Сдерживайте внутреннюю агрессию."; break;
        case 8: cout << "нарушение баланса, проблемы с детьми. Не обижайтесь на людей."; break;
        case 9: cout << "одиночество, презрение к глупцам. Избавьтесь от гордыни."; break;
        case 10: cout << "неумение жить своей жизнью, недостаток ответственности. Много работайте."; break;
        case 11: cout << "раздражение от чужой медлительности. Не гнобите других, реализуйте свой потенциал."; break;
        case 12: cout << "неумение служить, вынужденная жертва. Поверьте в то, что добро возвращается."; break;
        case 13: cout << "ранний уход из жизни, желание прожить долгую жизнь. Помогайте больным, старикам и немощным."; break;
        case 14: cout << "сомнение в своих талантах, страх зависимостей. Зарабатывайте на таланте."; break;
        case 15: cout << "раненое эго, проблемы в отношениях с миром. Помогайте людям, будьте независимы."; break;
        case 16: cout << "разрушения в прошлой и текущей жизни себя и других людей. Проработайте внутреннюю агрессию."; break;
        case 17: cout << "звездная болезнь, непризнание окружающими. Помогайте другим людям реализовать талант."; break;
        case 18: cout << "занятия магией, злоупотребление силой. Направьте потенциал на благо людям."; break;
        case 19: cout << "обман в благотворительности, потребность служить людям. Будьте щедрее."; break;
        case 20: cout << "плохие отношения с родителями, проблемы в семье. Примите близких такими, как есть."; break;
        case 21: cout << "занятие негативной деятельностью, искушение вредить людям. Будьте миротворцем."; break;
        case 22: cout << "зависимости любого рода, ревность. Будьте свободны и признайте свободу других людей."; break;
        default: cout << "неизвестное кармическое число.";
    }
    cout << endl;
}

struct tail {
    int bottom;
    int first;
    int second;
    int third;
};

tail numTail(int day, int month, int year) {
    tail result;
    
    // Правый угол (год)
    int year_sum = 0;
    int temp = year;
    while (temp > 0) {
        year_sum += temp % 10;
        temp /= 10;
    }
    if (year_sum > 22) year_sum = toSingle (year_sum);
    
    // Нижний угол
    result.bottom = day + month + year_sum;
    if (result.bottom > 22) result.bottom = toSingle (result.bottom);
    
    // Центр
    int center = day + month + year_sum + result.bottom;
    center = toSingle (center);
    
    // Кармический хвост
    result.first = center + result.bottom;
    if (result.first > 22) result.first = toSingle (result.first);
    
    result.second = result.first + result.bottom;
    if (result.second > 22) result.second = toSingle (result.second);
    
    result.third = result.second + result.bottom;
    if (result.third > 22) result.third = toSingle (result.third);
    
    return result;
}

int main() {
    
    setlocale(LC_ALL, "Russian"); // Для поддержки русского языка в консоли

    State currentState = START;
    string input, name;
    int day = 0, month = 0, year = 0;
    int nameNumber = 0, birthNumber = 0, totalNumber = 0;
    tail karmicTail;
    
    cout << "Введите ваше имя на английском и дату рождения (дд мм гггг): ";
    getline(cin, input);
    
    stringstream ss(input);
    
    while (currentState != END) {
        switch(currentState) {
            case START:
                currentState = READ_NAME;
                break;
                
            case READ_NAME:
                if (!(ss >> name)) {
                    currentState = ERROR;
                    break;
                }
                currentState = READ_DAY;
                break;
                
            case READ_DAY:
                if (!(ss >> day) || day < 1 || day > 31) {
                    currentState = ERROR;
                    break;
                }
                currentState = READ_MONTH;
                break;
                
            case READ_MONTH:
                if (!(ss >> month) || month < 1 || month > 12) {
                    currentState = ERROR;
                    break;
                }
                currentState = READ_YEAR;
                break;
                
            case READ_YEAR:
                if (!(ss >> year) || year < 1000 || year > 9999) {
                    currentState = ERROR;
                    break;
                }
                currentState = CALC_NAME_NUMBER;
                break;
                
            case CALC_NAME_NUMBER:
                for (char c : name) {
                    nameNumber += letToNum(c);
                }
                nameNumber = toSingle (nameNumber);
                currentState = CALC_BIRTH_NUMBER;
                break;
                
            case CALC_BIRTH_NUMBER:
                birthNumber = toSingle (day + month + toSingle (year));
                currentState = CALC_TOTAL_NUMBER;
                break;
                
            case CALC_TOTAL_NUMBER:
                totalNumber = toSingle (nameNumber + birthNumber);
                currentState = CALC_KARMIC_TAIL;
                break;
                
            case CALC_KARMIC_TAIL:
                karmicTail = numTail(day, month, year);
                currentState = PRINT_RESULTS;
                break;
                
            case PRINT_RESULTS:
                cout << "\n=== Результаты расчета ===" << endl;
                cout << "Число имени: " << nameNumber << " - ";
                char1(nameNumber);
                
                cout << "Число даты рождения: " << birthNumber << " - ";
                char1(birthNumber);
                
                cout << "Общее число судьбы: " << totalNumber << " - ";
                char1(totalNumber);
                
                cout << "\nКармический хвост: "
                     << karmicTail.first << "-" 
                     << karmicTail.second << "-" 
                     << karmicTail.third << endl;
                
                cout << "\nРасшифровка кармического хвоста:" << endl;
                cout << "Первое число: "; printTail(karmicTail.first);
                cout << "Второе число: "; printTail(karmicTail.second);
                cout << "Третье число: "; printTail(karmicTail.third);
                
                currentState = END;
                break;
                
            case ERROR:
                cout << "Ошибка ввода! Пожалуйста, введите данные в формате: Имя дд мм гггг" << endl;
                
                currentState = END;
                break;
                
            case END:
                break;
        }
    }
    
    return 0;
}