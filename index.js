document.addEventListener('DOMContentLoaded', () => {
    const loginForm = document.querySelector('.login');
    const accountSection = document.getElementById('account');
    const balanceDisplay = document.getElementById('Balance');
    let balance = 2.5;

    const validCredentials = {
        username: 'admin',
        password: 'Treehouse'
    };

    loginForm.addEventListener('submit', (Event) => {
        Event.preventDefault();
        const username = document.getElementById('Usuario').value;
        const password = document.getElementById('Contraseña').value;

        if (username === validCredentials.username && password === validCredentials.password) {
            accountSection.style.display = 'block';
            loginForm.style.display = 'none';
        } else {
            alert('Usuario o contraseña incorrectos');
        }
    });

    document.getElementById('checkBalance').addEventListener('click', () => {
            balanceDisplay.textContent = `Saldo: ${balance.toFixed(2)}`;
    });

    document.getElementById('deposit').addEventListener('click', () => {
        const amount = parseFloat(prompt('Ingrese la cantidad que desea depositar: '));
        if (!isNaN(amount) && amount > 0) {
            balance += amount;
            balanceDisplay.textContent = `Saldo: ${balance.toFixed(2)}`;
        } else {
            prompt('Ingrese una cantidad válida');
        }
    })
})