require 'find'

Find.find('c:/temp') do |f|
    # print file and path to screen if filename ends in ".mp3"
    puts f if f.match(/\.sql\Z/)
end
