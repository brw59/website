//For project tabs

// THIS IS NOT WORKING YET


//function closeUnnecessaryTabs() {
//;	
//}

$('.projectCollapse').click(function () {
	alert("made it");
//    $(this).find('span').text(function (_, value) {
//       alert(value); 
//		 return value == '-' ? '+' : '-';
//    });
    $(this).nextUntil('tr.projectCollapse').slideToggle(100, function () {alert("made it inside func");});
});


$headers.find('span').text('+');
$('table tr:not(.projectCollapse)').hide();

