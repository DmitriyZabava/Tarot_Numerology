#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <string>
#include <cstdlib>
#include <cstring>

using namespace std;

// Структура для хранения карты Таро
struct TarotCard {
    string id;          // Уникальный идентификатор карты
    string name;
    bool isMajor;       // Старший аркан или нет
    bool isPositive;    // Положительная карта или отрицательная
    string description; // Краткое описание значения
};

// Функция для создания колоды Таро
vector<TarotCard> createDeck() {
    vector<TarotCard> deck;

    // Старшие арканы (22 карты)
      vector<TarotCard> majorArcana = {
        {"HA001", "Шут", true, true, "Новые начинания, спонтанность, свободный дух"},
        {"HA002", "Маг", true, true, "Сила воли, творчество, мастерство"},
        {"HA003", "Верховная Жрица", true, true, "Интуиция, тайны, мудрость"},
        {"HA004", "Императрица", true, true, "Плодородие, изобилие, природа"},
        {"HA005", "Император", true, true, "Авторитет, структура, контроль"},
        {"HA006", "Иерофант", true, true, "Традиции, духовность, обучение"},
        {"HA007", "Влюбленные", true, true, "Любовь, гармония, отношения"},
        {"HA008", "Колесница", true, true, "Победа, воля, успех"},
        {"HA009", "Сила", true, true, "Сила духа, сострадание, влияние"},
        {"HA010", "Отшельник", true, false, "Самоанализ, одиночество, поиск"},
        {"HA011", "Колесо Фортуны", true, true, "Судьба, удача, поворотные моменты"},
        {"HA012", "Справедливость", true, true, "Баланс, правда, закон"},
        {"HA013", "Повешенный", true, false, "Жертва, пауза, новый взгляд"},
        {"HA014", "Смерть", true, false, "Конец, трансформация, переход"},
        {"HA015", "Умеренность", true, true, "Баланс, терпение, гармония"},
        {"HA016", "Дьявол", true, false, "Искушение, зависимость, материализм"},
        {"HA017", "Башня", true, false, "Крах, неожиданные изменения, откровение"},
        {"HA018", "Звезда", true, true, "Надежда, вдохновение, духовность"},
        {"HA019", "Луна", true, false, "Иллюзии, тревога, подсознание"},
        {"HA020", "Солнце", true, true, "Радость, успех, жизненная сила"},
        {"HA021", "Суд", true, true, "Возрождение, призыв, прощение"},
        {"HA022", "Мир", true, true, "Завершение, единство, достижение"}
    };

        // Младшие арканы - Жезлы (Wands)
    vector<TarotCard> minorArcanaWands = {
        {"SAJ001", "Туз Жезлов", false, true, "Творческое начало, энергия, вдохновение"},
        {"SAJ002", "Двойка Жезлов", false, true, "Планирование, будущие решения"},
        {"SAJ003", "Тройка Жезлов", false, true, "Первые успехи, ожидание"},
        {"SAJ004", "Четверка Жезлов", false, true, "Празднование, гармония"},
        {"SAJ005", "Пятерка Жезлов", false, false, "Конфликт, соперничество"},
        {"SAJ006", "Шестерка Жезлов", false, true, "Победа, признание"},
        {"SAJ007", "Семерка Жезлов", false, false, "Защита, отстаивание позиции"},
        {"SAJ008", "Восьмерка Жезлов", false, true, "Быстрое движение, новости"},
        {"SAJ009", "Девятка Жезлов", false, false, "Устойчивость, защита"},
        {"SAJ010", "Десятка Жезлов", false, false, "Бремя, ответственность"},
        {"SAJ011", "Король жезлов", false, true, "Зрелый мудрый человек, старше вопрошающего, властный, энергичный"},
        {"SAJ012", "Королева жезлов", false, true, "Женская фигура, обдуманные решения, стремление к самореализации, энергия бьёт ключем"},
        {"SAJ013", "Рыцарь жезлов", false, false, "Непостоянный импульсивный человек, энергетические качели"},
        {"SAJ014", "Паж жезлов", false, true, "Амбициозный молодой человек"}
    };

    // Младшие арканы - Кубки (Cups)
    vector<TarotCard> minorArcanaCups = {
        {"SAK001", "Туз Кубков", false, true, "Любовь, новые чувства"},
        {"SAK002", "Двойка Кубков", false, true, "Связь, партнерство"},
        {"SAK003", "Тройка Кубков", false, true, "Празднование, дружба"},
        {"SAK004", "Четверка Кубков", false, false, "Апатия, упущенные возможности"},
        {"SAK005", "Пятерка Кубков", false, false, "Потеря, сожаление"},
        {"SAK006", "Шестерка Кубков", false, true, "Ностальгия, детские воспоминания"},
        {"SAK007", "Семерка Кубков", false, false, "Иллюзии, выбор"},
        {"SAK008", "Восьмерка Кубков", false, false, "Уход, поиск глубины"},
        {"SAK009", "Девятка Кубков", false, true, "Удовлетворение, исполнение желаний"},
        {"SAK010", "Десятка Кубков", false, true, "Счастье, гармония в семье"},
        {"SAK011", "Король Кубков", false, true, "Пассивный мудрый богатый мужчина"},
        {"SAK012", "Королева Кубков", false, true, "Мечтательная добрая женщина"},
        {"SAK013", "Рыцарь Кубков", false, true, "Приятные новости, творческая личность"},
        {"SAK014", "Паж Кубков", false, true, "Наивный инфантильный мальчик"}
    };

    // Младшие арканы - Мечи (Swords)
    vector<TarotCard> minorArcanaSwords = {
        {"SAM001", "Туз Мечей", false, true, "Прорыв, ясность"},
        {"SAM002", "Двойка Мечей", false, false, "Тупик, трудный выбор"},
        {"SAM003", "Тройка Мечей", false, false, "Сердечная боль, печаль"},
        {"SAM004", "Четверка Мечей", false, true, "Отдых, восстановление"},
        {"SAM005", "Пятерка Мечей", false, false, "Конфликт, победа любой ценой"},
        {"SAM006", "Шестерка Мечей", false, true, "Переход, движение вперед"},
        {"SAM007", "Семерка Мечей", false, false, "Обман, хитрость"},
        {"SAM008", "Восьмерка Мечей", false, false, "Ограничения, беспомощность"},
        {"SAM009", "Девятка Мечей", false, false, "Тревога, страх"},
        {"SAM010", "Десятка Мечей", false, false, "Конец, болезненное поражение"},
        {"SAM011", "Король Мечей", false, true, "Безэмоциональный властный мужчина"},
        {"SAM012", "Королева Мечей", false, false, "Вдова, трудный опыт"},
        {"SAM013", "Рыцарь Мечей", false, false, "Военное вторжение, агрессивная личность"},
        {"SAM014", "Паж Мечей", false, false, "Плохие новости, инфантильный подросток"},
    };

    // Младшие арканы - Пентакли (Pentacles)
    vector<TarotCard> minorArcanaPentacles = {
        {"SAP001", "Туз Пентаклей", false, true, "Процветание, новые возможности"},
        {"SAP002", "Двойка Пентаклей", false, true, "Баланс, адаптация"},
        {"SAP003", "Тройка Пентаклей", false, true, "Работа в команде, мастерство"},
        {"SAP004", "Четверка Пентаклей", false, false, "Жадность, контроль"},
        {"SAP005", "Пятерка Пентаклей", false, false, "Финансовые трудности"},
        {"SAP006", "Шестерка Пентаклей", false, true, "Щедрость, помощь"},
        {"SAP007", "Семерка Пентаклей", false, true, "Терпение, ожидание результатов"},
        {"SAP008", "Восьмерка Пентаклей", false, true, "Усердная работа, мастерство"},
        {"SAP009", "Девятка Пентаклей", false, true, "Удовлетворение, комфорт"},
        {"SAP010", "Десятка Пентаклей", false, true, "Богатство, семейное благополучие"},
        {"SAP011", "Король Пентаклей", false, true, "Предприниматель, прагматичный"},
        {"SAP012", "Королева Пентаклей", false, true, "Экономная, хозяйственная женщина"},
        {"SAP013", "Рыцарь Пентаклей", false, true, "Труд, упорство, работящий человек"},
        {"SAP014", "Паж Пентаклей", false, true, "Трудолюбивый подмастерье"}
    };

    // Добавляем все карты в колоду
    deck.insert(deck.end(), majorArcana.begin(), majorArcana.end());
    deck.insert(deck.end(), minorArcanaWands.begin(), minorArcanaWands.end());
    deck.insert(deck.end(), minorArcanaCups.begin(), minorArcanaCups.end());
    deck.insert(deck.end(), minorArcanaSwords.begin(), minorArcanaSwords.end());
    deck.insert(deck.end(), minorArcanaPentacles.begin(), minorArcanaPentacles.end());

    return deck;
}

// Функция для парсинга QUERY_STRING
int parseQueryString(const char* query) {
    if (query == nullptr) return 2; // По умолчанию низкая точность
    
    string qs(query);
    size_t pos = qs.find("accuracy=");
    if (pos == string::npos) return 2;
    
    string val = qs.substr(pos + 9, 1);
    if (val == "1") return 1;
    return 2;
}

int main() {
    // Устанавливаем заголовок Content-Type для JSON
    cout << "Content-Type: application/json\n\n";
    
    // Получаем QUERY_STRING
    const char* query = getenv("QUERY_STRING");
    int accuracy = parseQueryString(query);
    
    // Создаем колоду
    vector<TarotCard> deck = createDeck();

    // Фильтруем колоду в зависимости от точности
    vector<TarotCard> filteredDeck;
    if (accuracy == 1) {
        copy_if(deck.begin(), deck.end(), back_inserter(filteredDeck), 
            [](const TarotCard& card) { return card.isMajor; });
    } else {
        filteredDeck = deck;
    }

    // Перемешиваем колоду
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(filteredDeck.begin(), filteredDeck.end(), default_random_engine(seed));

    // Вытаскиваем 3 карты
    vector<TarotCard> spread;
    for (int i = 0; i < 3 && i < filteredDeck.size(); ++i) {
        spread.push_back(filteredDeck[i]);
    }

    // Подсчитываем положительные и отрицательные карты
    int positiveCount = 0;
    int negativeCount = 0;
    for (const auto& card : spread) {
        if (card.isPositive) {
            positiveCount++;
        } else {
            negativeCount++;
        }
    }

    // Формируем JSON-ответ
    cout << "{\n";
    cout << "  \"cards\": [\n";
    for (size_t i = 0; i < spread.size(); ++i) {
        cout << "    {\n";
        cout << "      \"id\": \"" << spread[i].id << "\",\n";
        cout << "      \"name\": \"" << spread[i].name << "\",\n";
        cout << "      \"description\": \"" << spread[i].description << "\",\n";
        cout << "      \"isPositive\": " << (spread[i].isPositive ? "true" : "false") << "\n";
        cout << "    }" << (i < spread.size() - 1 ? "," : "") << "\n";
    }
    cout << "  ],\n";
    cout << "  \"outcome\": \"" << (positiveCount >= 2 ? "Благополучный! В вашей ситуации преобладают положительные энергии." : 
                                  (negativeCount >= 2 ? "Неблагоприятный. Будьте осторожны, возможны трудности." : 
                                  "Нейтральный. В вашей ситуации баланс положительных и отрицательных влияний.")) << "\"\n";
    cout << "}\n";

    return 0;
}