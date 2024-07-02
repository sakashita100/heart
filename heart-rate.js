document.addEventListener("DOMContentLoaded", function() {
    const heartRateElement = document.getElementById('heart-rate');
    const heartRateInput = document.getElementById('heart-rate-input');
    const setHeartRateButton = document.getElementById('set-heart-rate');

    function setHeartRate() {
        const heartRate = heartRateInput.value;
        if (heartRate) {
            heartRateElement.textContent = heartRate;
        }
    }

    setHeartRateButton.addEventListener('click', setHeartRate);
});
