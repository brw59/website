/*
append an endline at the end of each inner div inside the body
NOT WORKING RIGHT NOW
*/
/* $( "content div" ).append( "<p>Test</p>" ); */
/*
function addEndlineToDiv() {
	var firstLevelDivTags = $("section").children;
	
	
	firstLevelDivTags.each(function() {
		this.content() += "<p>test</p>"; // really what I want to do is to add a '<br>' here 
	})
	
}
*/
 
/*
This javaScript implementation idea was taken from here:
http://www.w3schools.com/js/js_whereto.asp
*/

function setup(evt, cityName) {
	openCity(evt, cityName);
	calculateBirthday();
}

function openCity(evt, cityName) {
    var i, tabcontent, tablinks;
    tabcontent = document.getElementsByClassName("tabcontent");
	
    for (i = 0; i < tabcontent.length; i++) {
        tabcontent[i].style.display = "none";
    }
    tablinks = document.getElementsByClassName("tablinks");
	
	var nameOfTab = cityName + "Tab";
	
    for (i = 0; i < tabcontent.length; i++) {
		 
		 tablinks[i].className = tablinks[i].className.replace(" active", "");
		 
		 if (nameOfTab == tablinks[i].parentElement.getAttribute("name")) {
		 	tablinks[i].parentElement.setAttribute("id", "selected");
		 } else {
			 tablinks[i].parentElement.setAttribute("id", "");
		 }
    }
	
	if (cityName == "projects") {
//		alert("this is an alert");
//		$headers;
		;
	}
	
	
    document.getElementById(cityName).style.display = "block";
	
   evt.currentTarget.className += " active";

	/*
	 who knows why this doesn't work ... I don't know javaScript well enough to
	 figure out how to make it right, but this would be a simpler solution than
	 what I figured out to do above
	*/
//	evt.currentTarget.ELEMENT_NODE.parentElement.setAttribute("id", "selected");
}


/*
Calculate my age from my birthday part
Edited from here:
http://www.mysamplecode.com/2011/10/javascript-calculate-age-from-birthdate.html
*/
function calculateBirthday(birthdayDate) {
	var birthdayDate = "10/19/1992" // this is my birthday
	
	/*
		I don't really need to validate, since I'm puting my birthday in statically,
		but it was good practice ... and it works too!
	*/
	document.getElementById("myAge").innerHTML = birthdayDate

	// removes leading spaces, had it been typed in instead
	var stripString = /^\s*/;
	var inputBirthday = birthdayDate;
	inputBirthday = inputBirthday.replace(stripString, "");
	birthdayDate = inputBirthday;
	
	document.getElementById("myAge").innerHTML = birthdayDate
	
	datemsg = isValidDate(inputBirthday);
	if (datemsg != "") {
		alert(datemsg); // Maybe change the innerHTML instead?
		return;
	}
	else {
		//Now find the Age based on the Birth Date
		getAge(new Date(inputBirthday));
	}
}

function getAge(birth) {
	
	 var today = new Date();
	 var nowyear = today.getFullYear();
	 var nowmonth = today.getMonth();
	 var nowday = today.getDate();

	 var birthyear = birth.getFullYear();
	 var birthmonth = birth.getMonth();
	 var birthday = birth.getDate();

	 var age = nowyear - birthyear;
	 var age_month = nowmonth - birthmonth;
	 var age_day = nowday - birthday;
	
	if(age_month < 0 || (age_month == 0 && age_day <0)) {
		age = parseInt(age) -1;
	}
	
	if (age_month == 0 && age_day == 0) {
		document.getElementById("myAge").innerHTML = "Today is my birthday! I just turned " + age;
	} else {
		document.getElementById("myAge").innerHTML = "I am " + age;
	}
}

function isValidDate(dateStr) {


	var msg = "";
	// Checks for the following valid date formats:
	// MM/DD/YY   MM/DD/YYYY   MM-DD-YY   MM-DD-YYYY
	// Also separates date into month, day, and year variables

	// To require a 2 & 4 digit year entry, use this line instead:
	//var datePat = /^(\d{1,2})(\/|-)(\d{1,2})\2(\d{2}|\d{4})$/;
	// To require a 4 digit year entry, use this line instead:
	var datePat = /^(\d{1,2})(\/|-)(\d{1,2})\2(\d{4})$/;

	var matchArray = dateStr.match(datePat); // is the format ok?
	if (matchArray == null) {
		msg = "Date is not in a valid format.";
		return msg;
	}

	 month = matchArray[1]; // parse date into variables
	 day = matchArray[3];
	 year = matchArray[4];


	 if (month < 1 || month > 12) { // check month range
		  msg = "Month must be between 1 and 12.";
		  return msg;
	 }

	 if (day < 1 || day > 31) {
		  msg = "Day must be between 1 and 31.";
		  return msg;
	 }

	 if ((month==4 || month==6 || month==9 || month==11) && day==31) {
		  msg = "Month "+month+" doesn't have 31 days!";
		  return msg;
	 }

	 if (month == 2) { // check for february 29th
		var isleap = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
	 
		if (day>29 || (day==29 && !isleap)) {
			msg = "February " + year + " doesn't have " + day + " days!";
			return msg;
		}
	 }

	 if (day.charAt(0) == '0') day= day.charAt(1);

	 //Incase you need the value in CCYYMMDD format in your server program
	 //msg = (parseInt(year,10) * 10000) + (parseInt(month,10) * 100) + parseInt(day,10);

	 return msg;  // date is valid
}

