class PagesController < ApplicationController

	def home 
		render 'home.html.erb'
	end
	
	def members
		render 'members.html.erb'
	end
end
