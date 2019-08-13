"use strict";

const navToggle = document.querySelector('.menu-icon');
const sidebar = document.querySelector('.sidebar')
document.querySelector('.menu-button').addEventListener('click', toggleNavigation);

function toggleNavigation() {
	sidebar.classList.toggle('show');
	navToggle.classList.toggle('change');
}
