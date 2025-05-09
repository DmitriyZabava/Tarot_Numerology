function getTarotReading() {
	const accuracy = document.getElementById("accuracy").value;
	const resultDiv = document.getElementById("result");
	const cardsDiv = document.getElementById("cards");
	const outcomeDiv = document.getElementById("outcome");

	// Показываем индикатор загрузки
	cardsDiv.innerHTML = "<p>Загрузка...</p>";
	resultDiv.style.display = "block";

	const localUrl = `./static/tarot.exe?accuracy=${accuracy}`;
	const serverUrl = `/cgi-bin/tarot.exe?accuracy=${accuracy}`;
	// Отправляем запрос к CGI-скрипту
	fetch(localUrl)
		.then((response) => response.json())
		.then((data) => {
			// Очищаем контейнер для карт
			cardsDiv.innerHTML = "";
			console.log(data);

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
		})
		.catch((error) => {
			cardsDiv.innerHTML =
				"<p>Произошла ошибка при получении расклада. Пожалуйста, попробуйте снова.</p>";
			console.error("Error:", error);
		});
}
