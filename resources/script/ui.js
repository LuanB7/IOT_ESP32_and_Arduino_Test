function modal(modalId, status) {
    let modalDOM = document.querySelector(`#${modalId}`);
    let blackBack = document.querySelector(".black-back");

    if (status) {
        modalDOM.classList.add("visible");
        blackBack.classList.add("visible");
    } else {
        modalDOM.classList.remove("visible");
        blackBack.classList.remove("visible");
    }
}