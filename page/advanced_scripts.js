const showAdvancedSettingsButton = document.getElementById('show-advanced-settings-button');
const closeAdvancedSettingsButton = document.getElementById('close-advanced-settings-button');
const advancedSettingsContainer = document.getElementById('advanced-settings-container');

showAdvancedSettingsButton.onclick = () => {
    advancedSettingsContainer.classList.remove('hide');
}

closeAdvancedSettingsButton.onclick = () => {
    advancedSettingsContainer.classList.add('hide');
}