document.querySelector("button").addEventListener("click", getTarotReading);

async function getTarotReading() {
	const accuracy = document.getElementById("accuracy").value;
	const resultDiv = document.getElementById("result");
	const cardsDiv = document.getElementById("cards");
	const outcomeDiv = document.getElementById("outcome");

	// Показываем индикатор загрузки
	cardsDiv.innerHTML = "<p>Загрузка...</p>";
	resultDiv.style.display = "block";

	try {
		// Отправляем запрос к CGI-скрипту
		const response = await fetch(
			`/cgi-bin/tarot.exe?accuracy=${accuracy}`
		);

		// Проверяем статус ответа
		if (!response.ok) {
			throw new Error(`HTTP error! status: ${response.status}`);
		}

		const data = await response.json();

		// Очищаем контейнер для карт
		cardsDiv.innerHTML = "";

		// Добавляем карты в результат
		data.cards.forEach((card) => {
			const cardDiv = document.createElement("div");
			cardDiv.className = `card ${
				card.isPositive ? "positive" : "negative"
			}`;
			cardDiv.innerHTML = `
                <h3>${card.name}</h3>
                <img src="../static/cards/${card.id}.jpg">
                <p>${card.description}</p>
                <p><strong>Тип:</strong> ${
					card.isPositive ? "Положительная" : "Отрицательная"
				}</p>
            `;
			cardsDiv.appendChild(cardDiv);
		});

		// Добавляем общий исход
		outcomeDiv.textContent = data.outcome;
	} catch (error) {
		cardsDiv.innerHTML =
			"<p>Произошла ошибка при получении данных сервера. Пожалуйста, попробуйте снова.</p>";
		console.error("Error:", error);
	}
}
