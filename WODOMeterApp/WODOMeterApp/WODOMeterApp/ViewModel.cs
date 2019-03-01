using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Text;
using System.Threading.Tasks;
using Plugin.BLE;
using Plugin.BLE.Abstractions.Contracts;
using Plugin.BLE.Abstractions.EventArgs;

namespace WODOMeterApp
{
    public class ViewModel : INotifyPropertyChanged
    {
        // Events

        public event PropertyChangedEventHandler PropertyChanged;

        // Methods
        public async Task Start()
        {
            try
            {
                ble = CrossBluetoothLE.Current;
                adapter = CrossBluetoothLE.Current.Adapter;
                device = await adapter.ConnectToKnownDeviceAsync(Guid.Parse("6705A451-4832-E064-03B0-AE177889C59F"));
                service = await device.GetServiceAsync(Guid.Parse("6C76DEFE-A465-4437-8276-01146E567164"));
                characteristic = await service.GetCharacteristicAsync(Guid.Parse("9CAAF395-F500-451E-B47E-21761EDC1290"));
                characteristic.ValueUpdated += Characteristic_ValueUpdated;
                await characteristic.StartUpdatesAsync();
            }
            catch (Exception)
            {
            }
        }

        private void Characteristic_ValueUpdated(object sender, CharacteristicUpdatedEventArgs e)
        {
            try
            {
                Measurement = BitConverter.ToInt32(e.Characteristic.Value, 0);
            }
            catch(Exception)
            {
            }
        }

        // Properties
        public int Measurement
        {
            get { return measurement; }
            private set
            {
                measurement = value;
                PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(nameof(Measurement)));
            }
        }

        // Fields
        private IBluetoothLE ble;
        private IAdapter adapter;
        private IDevice device;
        private IService service;
        private ICharacteristic characteristic;
        private int measurement;
    }
}
