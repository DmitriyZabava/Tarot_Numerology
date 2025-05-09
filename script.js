document.addEventListener("DOMContentLoaded", () => {
	const taroBtn = document.getElementById("taroBtn");
	const numeroBtn = document.getElementById("numeroBtn");

	taroBtn.addEventListener("click", async () => {
		try {
			const response = await fetch("/cgi-bin/taro.exe");
			const data = await response.json();
			console.log(data);
		} catch (error) {
			console.error("Ошибка при получении данных:", error);
			alert("Ошибка при получении данных");
		}
	});

	numeroBtn.addEventListener("click", async () => {
		try {
			const response = await fetch("/cgi-bin/numero.exe");
			const data = await response.json();
			console.log(data);
		} catch (error) {
			console.error("Ошибка при получении данных:", error);
			alert("Ошибка при получении данных");
		}
	});
});
