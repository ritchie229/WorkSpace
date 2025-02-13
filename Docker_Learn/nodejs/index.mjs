import fs from 'fs'

fs.appendFile('my-textfile.txt', 'File created by Node.JS', (err) => {
    if (err) throw err
    console.log('File Saved!')
})

setTimeout(() =>console.log ('END'), 30000)