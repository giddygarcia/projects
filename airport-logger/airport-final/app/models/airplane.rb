class Airplane < ApplicationRecord
	validates :code, presence:true, length:{maximum: 20}
	validates :seat_capacity, presence:true, length:{maximum: 4}
	validates :destination, presence:true
	validates :time_in, presence:true
	validates :time_out, presence:true
end