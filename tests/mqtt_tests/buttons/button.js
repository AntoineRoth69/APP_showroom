let $ = require('jquery')

let button = $('<button/>', {
        text: 'click me',
        id: 'btn',
        click: function () { alert('hi'); }
    })

module.export = button