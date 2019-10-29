class CreateAirplanes < ActiveRecord::Migration[5.2]
  def change
    create_table :airplanes do |t|
      t.string :code
      t.integer :seat_capacity
      t.string :destination
      t.datetime :time_in
      t.datetime :time_out
      t.datetime :created_at
      t.datetime :updated_at

      t.timestamps
    end
  end
end
