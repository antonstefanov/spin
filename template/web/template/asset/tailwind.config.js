module.exports = {
  purge: {
    enabled: process.env.DEMO_ENV === 'production',
    mode: 'all',
    content: [
      '../lib/demo_web/templates/*.ml',
      '../lib/demo_web/views/*.ml',
      '../lib/demo_desgin/*.ml'
    ],
  },
  theme: {
    extend: {
      fontFamily: {
        sans: ['Inter var'],
      },
    },
  }
}
