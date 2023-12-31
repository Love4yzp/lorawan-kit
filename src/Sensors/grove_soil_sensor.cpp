#include "grove_soil_sensor.h"
#include "SensorsUtils.h"

grove_soil_sensor::grove_soil_sensor()
{
}
void grove_soil_sensor::init()
{
    // is_available = (Grove_I2C_Check(softwarei2c)) ? false : true;
    // is_available = (Grove_I2C_Check(Wire)) ? true : false;
    is_available = true;
}

bool grove_soil_sensor::read(struct sensor_data *sdata)
{
    uint16_t sum = 0, data[READ_NUM] = {0};
    double   variance = 0.0;
    init();
    if (!is_available) {
        return false;
    }
    analogRead(SOILPIN);
    delay(2);
    // 求和
    for (int i = 0; i < READ_NUM; i++) {
        data[i] = analogRead(SOILPIN);
        // LOGSS.print("Soil analog: ");
        // LOGSS.println(data[i]);
        delayMicroseconds(2);
        sum += data[i];
    }
    soil_value = sum / READ_NUM;
    // 求方差
    // for (int i = 0; i < READ_NUM; i++) {
    //     variance = variance + pow(data[i] - soil_value, 2);
    // }
    // variance = variance / READ_NUM;

    // if (variance > DATA_VARIANCE_MAX || soil_value > SOIL_DATA_MAX) {
    //     LOGSS.println(" Warning: Soil Sensor: " + String(soil_value) + " variance: " + String(variance));
    //     return false;
    // }
    
    LOGSS.println("Soil Sensor: " + String(soil_value)); // %, 0 - 100 -> 0-`10000
    sdata->data      = &soil_value;
    sdata->data_type = SENSOR_DATA_TYPE_INT32;
    sdata->size      = sizeof(soil_value);
    sdata->id        = GROVE_SOIL;
    sdata->name      = name;
    sdata->ui_type   = SENSOR_UI_TYPE_NORMAL;
    sdata->data_unit = data_unit;
    sdata->status    = true;
    return true;
}

const char *grove_soil_sensor::get_name()
{
    return "soil";
}

// grove_soil_sensor  buildin_soil;       // Serial.println("Measurement failed!");
