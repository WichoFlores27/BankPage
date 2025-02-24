document.addEventListener('DOMContentLoaded', () => {
    const loginForm = document.querySelector('.login');
    const accountSection = document.getElementById('account');
    const balanceDisplay = document.getElementById('Balance');
    let balance = 0.0;

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
})