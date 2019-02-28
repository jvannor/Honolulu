using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Xamarin.Forms;

namespace WODOMeterApp
{
    public partial class MainPage : ContentPage
    {
        // Methodfs
        public MainPage()
        {
            InitializeComponent();
            BindingContext = viewModel;
        }

        protected override async void OnAppearing()
        {
            base.OnAppearing();
            await viewModel.Start();
        }

        // Fields
        ViewModel viewModel = new ViewModel();
    }
}
