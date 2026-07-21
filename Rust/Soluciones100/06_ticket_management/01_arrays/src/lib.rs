// TODO: Flesh out the `WeekTemperatures` struct and its method implementations to pass the tests.

pub struct WeekTemperatures {
    // TODO
    temp: [Option<i32>; 7], //debe almacenar Option(Some, None) por que no puedo hacer un let kk: WeekTemperatures; como en C
}

#[derive(Copy, Clone)]
pub enum Weekday {
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday,
    Sunday,
}

impl WeekTemperatures {
    pub fn new() -> Self {
        //todo!()
        let week = WeekTemperatures { temp: [None; 7], };
        week
    }

    pub fn get_temperature(&self, day: Weekday) -> Option<i32> {
        //todo!()
        //self.temp.get(day as usize) devuelve un Option<&Option<i32>> con acceso a corchetes da lo que pide Option<i32>
        //esto confunde por que cuando se accede por corchetes se optione o el valor o un Panic! PERO hay que ver que el array es de Option<i32> asi que devolvera eso mismo.
        self.temp[day as usize] //necesita trait copy y clone para el Weekday. y el enum no es i32 sino usize. Rust es estricto
    }

    pub fn set_temperature(&mut self, day: Weekday, temperature: i32) {
        //todo!()
        self.temp[day as usize] = Some(temperature); //da un Option<i32> asi que o Some o None como valores admitidos
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_get_temperature() {
        let mut week_temperatures = WeekTemperatures::new();

        assert_eq!(week_temperatures.get_temperature(Weekday::Monday), None);
        assert_eq!(week_temperatures.get_temperature(Weekday::Tuesday), None);
        assert_eq!(week_temperatures.get_temperature(Weekday::Wednesday), None);
        assert_eq!(week_temperatures.get_temperature(Weekday::Thursday), None);
        assert_eq!(week_temperatures.get_temperature(Weekday::Friday), None);
        assert_eq!(week_temperatures.get_temperature(Weekday::Saturday), None);
        assert_eq!(week_temperatures.get_temperature(Weekday::Sunday), None);

        week_temperatures.set_temperature(Weekday::Monday, 20);
        assert_eq!(week_temperatures.get_temperature(Weekday::Monday), Some(20));

        week_temperatures.set_temperature(Weekday::Monday, 25);
        assert_eq!(week_temperatures.get_temperature(Weekday::Monday), Some(25));

        week_temperatures.set_temperature(Weekday::Tuesday, 30);
        week_temperatures.set_temperature(Weekday::Wednesday, 35);
        week_temperatures.set_temperature(Weekday::Thursday, 40);
        week_temperatures.set_temperature(Weekday::Friday, 45);
        week_temperatures.set_temperature(Weekday::Saturday, 50);
        week_temperatures.set_temperature(Weekday::Sunday, 55);

        assert_eq!(week_temperatures.get_temperature(Weekday::Monday), Some(25));
        assert_eq!(
            week_temperatures.get_temperature(Weekday::Tuesday),
            Some(30)
        );
        assert_eq!(
            week_temperatures.get_temperature(Weekday::Wednesday),
            Some(35)
        );
        assert_eq!(
            week_temperatures.get_temperature(Weekday::Thursday),
            Some(40)
        );
        assert_eq!(week_temperatures.get_temperature(Weekday::Friday), Some(45));
        assert_eq!(
            week_temperatures.get_temperature(Weekday::Saturday),
            Some(50)
        );
        assert_eq!(week_temperatures.get_temperature(Weekday::Sunday), Some(55));
    }
}
