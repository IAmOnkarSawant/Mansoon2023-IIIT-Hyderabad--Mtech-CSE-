document.addEventListener("DOMContentLoaded", function(){
    
    function validateTeamName() {
        const teamNameInput = document.getElementById('teamName');
        const teamNameError = document.getElementById('teamNameError');
        const teamName = teamNameInput.value;

        const uppercaseRegex = /[A-Z]/;
        const numericRegex = /[0-9]/;
        
        if (uppercaseRegex.test(teamName) && numericRegex.test(teamName)) {
            teamNameError.textContent = ''; 
            return true;
        } else {
            teamNameError.textContent = 'Invalid Username';
            return false;
        }
    }

    document.getElementById('teamName').addEventListener('input', validateTeamName);

    document.getElementById('teamRegistrationForm').addEventListener('submit', function (event) {
        if (!validateTeamName()) {
            event.preventDefault(); 
        }
    });
})

