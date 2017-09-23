$(document).ready(function() {
    $.ajax({
        url: "https://gdg-maceio-30f53.firebaseio.com/.json"
    }).then(function(data) {
       $('.buttonStatus').append(data.id);
       $('.ledStatus').append(data.content);
    });
});   