
let helper = require('./helper')

/**
 * Check to see if GPS data was transmitted and return a boolean
 * 
 * @param {number} address 
 * @param {number[]} data
 * @returns {boolean}
 */
exports.check = function check(address, data) {
    if(address == helper.TELEMETRY_ADDRESS.GPS){
        console.log("GPS: ")
        var gpsString = ""
        for (var index = 0; index < data.length; index++)
            gpsString += String.fromCharCode(data[index])
        //var gpsString = data.join('')
        var values = gpsString.split(',')

        //north and east is positive
        var longitudeStr = values[1]
        var latitudeStr = values[0]
        
        var longitude = String(parseFloat(longitudeStr) * (longitudeStr[longitudeStr.length - 1] == "W" ? -1 : 1))
        var latitude = String(parseFloat(latitudeStr) * (latitudeStr[latitudeStr.length - 1] == "S" ? -1 : 1))
        var speed = parseFloat(values[2])
        var heading = parseFloat(values[3])
        console.log(helper.DDMtoDD(longitude))
        console.log(helper.DDMtoDD(latitude))
        console.log(speed)
        console.log(heading)
    }
    return helper.addressCheck(
        address == helper.TELEMETRY_ADDRESS.GPS,
        () => {
        helper.sendData("gps", {
            "longitude": helper.DDMtoDD(longitude),
            "latitude": helper.DDMtoDD(latitude),
            "speed": speed,
            "heading": heading
        })
    })
}
