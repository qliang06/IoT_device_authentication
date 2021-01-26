
const SerialPort = require('serialport');
const sleep = require('sleep');

var random= 0; //#
var pk=0; //$
var sig=0; //--!
var count=0;

/* let Readline = SerialPort.parsers.Readline; // make instance of Readline parser
let parser = new Readline(); // make a new parser to read ASCII lines
myPort.pipe(parser); // pipe the serial stream to the parser
 */
var Readline = SerialPort.parsers.Readline;
var parser = new Readline();
var HostParser = new Readline();

//client, on the firt usb port of usb-hub
const port = new SerialPort('COM3', {baudRate : 115200},function (err) {
  if (err) {
    return console.log('Error: ', err.message);
  }
});

//host, on the third usb port of usb-hub
const hostport = new SerialPort('COM11', {baudRate : 115200},function (err) {
  if (err) {
    return console.log('Error: ', err.message);
  }
});

port.pipe(parser);
hostport.pipe(HostParser);


var askForRandom= function () {
	console.log('Sending Random number to client_board')
	hostport.write('#', function(err) {
		if (err) {
			return console.log('Error on write: ', err.message)
		  }
	})
}

var askForPublicKey= function () {
	
	port.write('@', function(err) {
	  if (err) {
		return console.log('Error on write: ', err.message)
	  }
	})

}

var askForSig= function () {
  port.write('@', function(err) {
	  if (err) {
		return console.log('Error on write: ', err.message)
	  }
  }) 
}

function sendToBoard(com, data) {
	com.write(data, function(err) {	
		if (err) {
			return console.log('Error on write: ', err.message)
		}
	  })
}

function clientSerialData(data) {
	if(data[0] =='$'){
		pk= 1;
	}
	else if(data[0] == '!') {
		sig =1;
	}
	else {
		console.log();
		if(pk==1) {
			var pk_hex= data.toString(16);
			var buffer = Buffer.from(pk_hex, 'hex');
			//console.log(buffer);
			sendToBoard(hostport, '$');
			sendToBoard(hostport, buffer);
			pk=0;
		}
		
		if(sig == 1) {
			var sig_hex= data.toString(16);
			var buffer = Buffer.from(sig_hex, 'hex');
			//console.log(buffer);
			sendToBoard(hostport, '!');
			sendToBoard(hostport, buffer);
			sig=0;
		}
		
		process.stdout.write(data.toString(16));
		console.log();
	}
}

function hostSerialData(data) {
	if(data[0] == '@' && count ==0) {
		setTimeout(askForPublicKey, 3000);
		count =1;
	}
	else if(data[0] =='@' && count ==1){
		setTimeout(askForSig, 5000); 
	}
	else if(data[0] =='#'){
		random= 1;
		//console.log(data)
	}
	else {
		console.log();
		if(random==1) {
			var random_hex= data.toString(16);
			var buffer = Buffer.from(random_hex, 'hex');
			//console.log(buffer);
			sendToBoard(port, '#');
			sendToBoard(port, buffer);
			random=0;
		}
		
		process.stdout.write(data.toString(16));
		console.log();
	}
}

parser.on('data', clientSerialData);
HostParser.on('data', hostSerialData);

setTimeout(askForRandom, 1000);

