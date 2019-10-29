class AirplanesController < ApplicationController

	def index
		@airplanes = Airplane.all
		render 'index.html.erb'
	end

	def new 
		@airplane = Airplane.new
		render 'new.html.erb'
	end

	def create 
		@airplane = Airplane.new(airplane_params)

		if @airplane.save
			flash[:notice] = "Sucessfully added a New Airplane"
			redirect_to airplanes_path(@airplane)
		else 
			render 'new.html.erb'
		end
	end

	def show 
		@airplane = Airplane.find(params[:id])
		render 'show.html.erb'
	end

	def edit 
		@airplane = Airplane.find(params[:id])
	end

	def update
		@airplane = Airplane.find(params[:id])

		if @airplane.update(airplane_params)
			flash[:notice] = "Update was successful"
			redirect_to airplane_path(@airplane)
		else
			render 'edit.html.erb'
		end	
	end

	def destroy
		@airplane = Airplane.find(params[:id])
		@airplane.destroy
		flash[:notice] = "Succesfully deleted airplane record with id: #{@airplane.id}, Code: #{@airplane.code}"
		redirect_to airplanes_path
	end

	private 
		def airplane_params
			params.require(:airplane).permit(:code, :seat_capacity, :destination, :time_in, :time_out)
		end

end