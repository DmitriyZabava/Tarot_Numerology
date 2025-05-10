document
	.getElementById("numerologyForm")
	.addEventListener("submit", async (e) => {
		e.preventDefault();

		const formData = new FormData(e.target);
		const params = new URLSearchParams(formData).toString();

		const localUrl = `./static/numero.exe?${params}`;
		const serverUrl = `/cgi-bin/numero.exe?${params}`;

		try {
			const response = await fetch(localUrl);
			if (!response.ok) throw new Error("Calculation failed");
			const data = await response.json();
			displayResults(data);
		} catch (error) {
			alert("Error: " + error.message);
		}
	});

function displayResults(data) {
	// Показываем блок результатов
	document.getElementById("results").classList.remove("hidden");

	// Заполняем данные
	document.getElementById("nameNumberValue").textContent =
		data.name_number.value;
	document.getElementById("nameNumberDesc").textContent =
		data.name_number.characteristic;

	document.getElementById("birthNumberValue").textContent =
		data.birth_number.value;
	document.getElementById("birthNumberDesc").textContent =
		data.birth_number.characteristic;

	document.getElementById("totalNumberValue").textContent =
		data.total_number.value;
	document.getElementById("totalNumberDesc").textContent =
		data.total_number.characteristic;

	// Кармический хвост
	const tailNumbers = data.karmic_tail.numbers.join(", ");
	const tailDescs = data.karmic_tail.descriptions
		.map(
			(desc, i) => `
        <div class="karmicTail">
        <img 
        src="../static/cards/HA0${
			data.karmic_tail.numbers[i] < 10
				? "0" + data.karmic_tail.numbers[i]
				: data.karmic_tail.numbers[i]
		}.jpg"
        width="150"
        height="225" 
        >
        <p><strong>${data.karmic_tail.numbers[i]} : </strong> ${desc}</p>
        </div>
        `
		)
		.join("");

	document.getElementById("karmicTailNumbers").textContent = tailNumbers;
	document.getElementById("karmicTailDescs").innerHTML = tailDescs;

	// Прокрутка к результатам
	document
		.getElementById("results")
		.scrollIntoView({ behavior: "smooth" });
}
