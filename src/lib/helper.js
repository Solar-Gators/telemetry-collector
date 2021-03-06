
const request = require('axios')
const config = require('config')

/**
 * Telemetry Addresses
 */
exports.TELEMETRY_ADDRESS = {
    GPS: 0,
    MPPT: 1,
    BMS: 2,
    IMU: 3
}


/**
* Sends data to the backend to be logged
*
* Examples:
* ```JavaScript
* sendData("bms", {
*     "packSumVoltage": 20
* })
* ```
* 
* ```JavaScript
* sendData("gps", {
*     "longitude": 1,
*     "latitude": -1,
*     "speed": 5,
*     "heading": 40
* })
* ```
*
* @param {String} url  url to route
* @param {{}} data data to send to route
*/
exports.sendData = function sendData(url, data)
{
    return request.post(`${config.get('server.url')}/api/${url}`, data)
}

/**
* Converts from Degrees Decimal Minutes (DDM) to Decimal Degree (DD) coordinates
* 
* DDM Format: DDMM.MMMM
* DD Format: DD.DDDDDD
* Example:
* ```JavaScript
* DDMtoDD(" -8220.366364") //returns -82.3394394
* ```
* @param {String} str DDM coordinates
*/
exports.DDMtoDD = function DDMtoDD(str)
{
    //get degrees
    var degrees = parseFloat(str[0] + str[1] + ( str[0] == '-' ? str[3] : ''));
    var minStr = ""
    for (var index = ( str[0] == '-' ? 3 : 2); index < str.length; index++)
    {
        minStr += str[index]
    }

    return degrees + (parseFloat(minStr)/60*( str[0] == '-' ? -1 : 1))
}


/**
* Converts two 8 bit number to a 16 bit unsigned number 
* 
* @param {Number} top    most sigificant byte
* @param {Number} bottom least significant byte
*/
exports.getWord = function getWord(top, bottom)
{
    return ((top << 8) | bottom)
}

/**
* Converts two 8 bit number to a 16 bit signed number 
* 
* @param {Number} top    most sigificant byte
* @param {Number} bottom least significant byte
*/
exports.signed16 = function signed16(top, bottom)
{
    var sign = top & (1 << 7);
    var x = (((top & 0xFF) << 8) | (bottom & 0xFF));
    if (sign)
        return 0xFFFF0000 | x;  // fill in most significant bits with 1's
    
    return x
}

/**
 * If condition is true then run callback. Always return condition
 * 
 * Examples:
 * ```JavaScript
 * addressCheck(true, () => console.log("Prints")) //Out: Prints
 * 
 * addressCheck(false, () => console.log("Does not Print")) //Out: Does not Print
 * ```
 * 
 * @param {boolean} condition
 * @param {Function} callback
 * @returns {boolean}
 */
exports.addressCheck = function addressCheck(condition, callback)
{
    if (condition)
    {
        callback()
    }
    return condition
}
