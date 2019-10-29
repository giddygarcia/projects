Rails.application.routes.draw do
  # For details on the DSL available within this file, see http://guides.rubyonrails.org/routing.html
  root to: 'pages#home'
  resources :airplanes
  get 'members', to: 'pages#members'
  get 'home', to: 'pages#home'
end
