document.addEventListener("DOMContentLoaded", function() {
    const heartRateElement = document.getElementById('heart-rate');

    function generateHeartRate() {
        const min = 60;
        const max = 100;
        const heartRate = Math.floor(Math.random() * (max - min + 1)) + min;
        heartRateElement.textContent = heartRate;
    }

    setInterval(generateHeartRate, 1000); // 1秒ごとに心拍数を更新
    generateHeartRate(); // 初回表示
});
