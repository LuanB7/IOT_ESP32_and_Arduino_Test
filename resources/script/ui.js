function modal(modalId, status, clearIpt=true) {
    let modalDOM = document.querySelector(`#${modalId}`);
    let blackBack = document.querySelector(".black-back");

    if (status) {

        if (clearIpt) {
            let ipts = modalDOM.querySelectorAll("input");
            ipts.forEach(ipt => {
                ipt.value = '';
            });
        }
        
        modalDOM.classList.add("visible");
        blackBack.classList.add("visible");

    } else {
        modalDOM.classList.remove("visible");
        blackBack.classList.remove("visible");
    }
}